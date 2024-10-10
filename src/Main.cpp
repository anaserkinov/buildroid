#include <cpprest/filestream.h>
#include <cpprest/http_client.h>
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <cpprest/uri.h>
#include <tgbot/tgbot.h>

#include <condition_variable>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>

#include "DatabaseController.hpp"
#include "FragmentManager.hpp"
#include "Fragments.hpp"
#include "GitManager.hpp"

using namespace TgBot;
using namespace web;
using namespace web::http;
using namespace web::http::client;

namespace fs = std::filesystem;

std::string KEY_TAXI_GIT_HOST = "TAXI_GIT_HOST";
std::string KEY_TAXI_GIT_TOKEN = "TAXI_GIT_TOKEN";
std::string KEY_TAXI_PROJECT_ID = "TAXI_GIT_PROJECT_ID";
std::string KEY_TAXI_TG_TEST_GROUP_ID = "TAXI_TG_TEST_GROUP_ID";
std::string KEY_TAXI_TG_GROUP_ID = "TAXI_TG_GROUP_ID";

std::string KEY_TAXI_USER_GIT_HOST = "TAXI_USER_GIT_HOST";
std::string KEY_TAXI_USER_GIT_TOKEN = "TAXI_USER_GIT_TOKEN";
std::string KEY_TAXI_USER_PROJECT_ID = "TAXI_USER_GIT_PROJECT_ID";
std::string KEY_TAXI_USER_TG_TEST_GROUP_ID = "TAXI_USER_TG_TEST_GROUP_ID";
std::string KEY_TAXI_USER_TG_GROUP_ID = "TAXI_USER_TG_GROUP_ID";

std::string KEY_BITO_GIT_HOST = "BITO_GIT_HOST";
std::string KEY_BITO_GIT_TOKEN = "BITO_GIT_TOKEN";
std::string KEY_BITO_PROJECT_ID = "BITO_GIT_PROJECT_ID";
std::string KEY_BITO_TG_TEST_GROUP_ID = "BITO_TG_TEST_GROUP_ID";
std::string KEY_BITO_TG_GROUP_ID = "BITO_TG_GROUP_ID";

std::string KEY_BITO_MARKET_GIT_HOST = "BITO_MARKET_GIT_HOST";
std::string KEY_BITO_MARKET_GIT_TOKEN = "BITO_MARKET_GIT_TOKEN";
std::string KEY_BITO_MARKET_PROJECT_ID = "BITO_MARKET_GIT_PROJECT_ID";
std::string KEY_BITO_MARKET_TG_TEST_GROUP_ID = "BITO_MARKET_TG_TEST_GROUP_ID";
std::string KEY_BITO_MARKET_TG_GROUP_ID = "BITO_MARKET_TG_GROUP_ID";

TgBot::Bot *bot = nullptr;
DatabaseController dbController;
std::unordered_map<std::string, std::string> configMap;

std::string lastUsedBranch = "";

std::mutex taskMtx;
std::condition_variable taskCV;
bool resumeTaskThread = true;

int64_t getInt64FromConfig(const std::string key) {
  return std::stol(configMap[key]);
}

std::string getContainerStatus(const std::string &containerName) {
  std::string command =
      "docker inspect --format '{{.State.Status}}' " + containerName;

  FILE *pipe = popen(command.c_str(), "r");
  if (!pipe) {
    std::cout << "Error executing command." << "\n";
    return "Error";
  }

  char buffer[128];
  std::string status;

  while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
    buffer[strcspn(buffer, "\n")] = '\0';
    status += buffer;
  }

  pclose(pipe);

  return status;
}

void gitWebhookThread() {
  // web::uri_builder uriB(U("http://localhost:8000"));
  web::uri_builder uriB(U("http://0.0.0.0:4040"));
  web::http::experimental::listener::http_listener listener(
      uriB.to_uri().to_string());

  listener.support(
      web::http::methods::POST, [](web::http::http_request request) {
        request.extract_json()
            .then([=](web::json::value request_data) {
              try {
                std::cout << "request: " << request_data << "\n";
                if (request.relative_uri().path() == "/gitlab") {
                  if (request_data.has_field("build_status") &&
                      request_data.has_field("build_stage")) {
                    auto status = request_data.at("build_status").as_string();
                    auto stage = request_data.at("build_stage").as_string();
                    if (status == "success" && stage == "build") {
                      auto projectId =
                          request_data.at("project_id").as_number().to_int64();
                      std::string project;
                      if (projectId ==
                          getInt64FromConfig(KEY_TAXI_PROJECT_ID)) {
                        project = "taxi_driver";
                      } else if (projectId ==
                                 getInt64FromConfig(KEY_BITO_PROJECT_ID)) {
                        project = "erp";
                      }

                      auto jobId =
                          request_data.at("build_id").as_number().to_int64();

                      try {
                        dbController.createSendTask(project, jobId);
                      } catch (const std::exception &e) {
                        std::cout << "Creating task error:" << e.what() << "\n";
                      }
                    }
                  }
                } else if (request.relative_uri().path() == "/github") {
                  if (request_data.has_field("action") &&
                      request_data.has_field("workflow_job") &&
                      request_data.at("action").as_string() == "completed") {
                    auto stage = request_data.at("workflow_job")
                                     .as_object()
                                     .at("name")
                                     .as_string();
                    if (stage == "build") {
                      auto projectId = request_data.at("repository")
                                           .as_object()
                                           .at("id")
                                           .as_number()
                                           .to_int64();
                      std::string project;
                      if (projectId ==
                          getInt64FromConfig(KEY_BITO_MARKET_PROJECT_ID)) {
                        project = "market";
                      } else if (projectId ==
                                 getInt64FromConfig(KEY_TAXI_USER_PROJECT_ID)) {
                        project = "taxi_user";
                      }

                      auto runId = request_data.at("workflow_job")
                                       .as_object()
                                       .at("run_id")
                                       .as_number()
                                       .to_int64();

                      try {
                        dbController.createSendTask(project, runId);
                      } catch (const std::exception &e) {
                        std::cout << "Creating task error:" << e.what() << "\n";
                      }
                    }
                  }
                }
              } catch (const std::exception &e) {
                std::cout << "Receiving post request error:" << e.what()
                          << "\n";
              }
            })
            .wait();
        request.reply(web::http::status_codes::OK);
      });

  listener.open()
      .then([]() { std::cout << "Listening git webhook" << std::endl; })
      .wait();

  while (true);
}

void tasksThread() {
  while (true) {
    std::unique_ptr<Task> task = dbController.getConfirmedTask();

    if (task != nullptr) {
      try {
        if (task->type == TASK_TYPE::SEND) {
          dbController.setTaskStatus(task->id, TASK_STATUS::COMPLETED);

          std::cout << "Task in progress: " << task->project << "\n";

          std::string downloadPath =
              "downloads/" + task->project + std::to_string(task->gitJobId);
          std::string outputPath =
              "downloads/" + task->project + std::to_string(task->gitJobId);

          std::string downloadUrl;
          std::string tokenKey;
          std::string gitToken;
          int64_t tgTestGroupId;
          int64_t tgGroupId;
          if (task->project == "taxi_driver") {
            tokenKey = "PRIVATE-TOKEN";
            gitToken = configMap[KEY_TAXI_GIT_TOKEN];
            tgTestGroupId = getInt64FromConfig(KEY_TAXI_TG_TEST_GROUP_ID);
            tgGroupId = getInt64FromConfig(KEY_TAXI_TG_GROUP_ID);
            downloadUrl = configMap[KEY_TAXI_GIT_HOST] + "/api/v4/projects/" +
                          configMap[KEY_TAXI_PROJECT_ID] + "/jobs/" +
                          std::to_string(task->gitJobId) + "/artifacts";
          } else if (task->project == "erp") {
            tokenKey = "PRIVATE-TOKEN";
            gitToken = configMap[KEY_BITO_GIT_TOKEN];
            tgTestGroupId = getInt64FromConfig(KEY_BITO_TG_TEST_GROUP_ID);
            tgGroupId = getInt64FromConfig(KEY_BITO_TG_GROUP_ID);
            downloadUrl = configMap[KEY_BITO_GIT_HOST] + "/api/v4/projects/" +
                          configMap[KEY_BITO_PROJECT_ID] + "/jobs/" +
                          std::to_string(task->gitJobId) + "/artifacts";
          } else {
            // github apps

            std::string getArtifactsUrl;
            downloadPath += "/outputs";

            if (task->project == "market") {
              tokenKey = "Authorization";
              gitToken = "Bearer " + configMap[KEY_BITO_MARKET_GIT_TOKEN];
              tgTestGroupId =
                  getInt64FromConfig(KEY_BITO_MARKET_TG_TEST_GROUP_ID);
              tgGroupId = getInt64FromConfig(KEY_BITO_MARKET_TG_GROUP_ID);
              getArtifactsUrl = configMap[KEY_BITO_MARKET_GIT_HOST] +
                                "/actions/runs/" +
                                std::to_string(task->gitJobId) + "/artifacts";
            } else if (task->project == "taxi_user") {
              tokenKey = "Authorization";
              gitToken = "Bearer " + configMap[KEY_TAXI_USER_GIT_TOKEN];
              tgTestGroupId = getInt64FromConfig(KEY_TAXI_USER_TG_GROUP_ID);
              tgGroupId = getInt64FromConfig(KEY_TAXI_USER_TG_GROUP_ID);
              getArtifactsUrl = configMap[KEY_TAXI_USER_GIT_HOST] +
                                "/actions/runs/" +
                                std::to_string(task->gitJobId) + "/artifacts";
            }

            uri url(U(getArtifactsUrl));
            http_client client(url);

            http_request request(methods::GET);
            request.headers().add(U(tokenKey), U(gitToken));

            try {
              client.request(request)
                  .then([&task](http_response response) {
                    return response.extract_json();
                  })
                  .then([&downloadUrl](json::value json_response) {
                    if (json_response.has_field(U("artifacts"))) {
                      auto artifacts = json_response[U("artifacts")].as_array();
                      for (const auto &artifact : artifacts) {
                        if (artifact.has_field(U("archive_download_url"))) {
                          downloadUrl =
                             artifact.at("archive_download_url").as_string();
                        }
                      }
                    }
                  })
                  .wait();
            } catch (const std::exception &e) {
                  std::cout << "Github artifacts error:" << e.what() << "\n";
            }
          }

          if (downloadUrl.length() != 0) {
            std::string downloadCmd = "rm -rf " + downloadPath;
            downloadCmd += " && rm -f " + downloadPath + ".zip";
            downloadCmd += " && mkdir -p " + downloadPath + " && curl -L -o ";
            downloadCmd += downloadPath + ".zip";
            downloadCmd += " --header ";
            downloadCmd += "\"" + tokenKey + ": ";
            downloadCmd += gitToken;
            downloadCmd += "\" ";
            downloadCmd += downloadUrl;
            downloadCmd += " && ";
            downloadCmd += "unzip " + downloadPath + ".zip ";
            downloadCmd += "-d " + downloadPath;
            downloadCmd += " && rm -f " + downloadPath + ".zip";
            std::cout << "downloadCmd: " << downloadCmd << "\n";
            auto downloadResult = Utils::execute(downloadCmd);
            if (downloadResult == "error") {
              dbController.setTaskStatus(task->id, TASK_STATUS::FAILED);
            } else {
              for (const auto &entry : fs::recursive_directory_iterator(
                       fs::current_path().string() + "/" + outputPath +
                       "/outputs/release")) {
                if (entry.is_regular_file() &&
                    entry.path().extension() == ".apk") {
                  try {
                    auto message = bot->getApi().sendDocument(
                        tgGroupId,
                        TgBot::InputFile::fromFile(
                            entry.path().string(),
                            "application/vnd.android.package-archive"),
                        "",
                        "#" + Utils::getVersionCode(entry.path().string()) +
                            "v" + Utils::getVersionName(entry.path().string()));
                    try {
                      bot->getApi().pinChatMessage(tgGroupId,
                                                   message->messageId);
                    } catch (const std::exception &e) {
                      std::cout << "Pin error:" << e.what() << "\n";
                    }
                  } catch (const std::exception &e) {
                    std::cout << "Message send error:" << e.what() << "\n";
                  }
                }
              }

              for (const auto &entry : fs::recursive_directory_iterator(
                       fs::current_path().string() + "/" + outputPath +
                       "/outputs/debug")) {
                if (entry.is_regular_file() &&
                    entry.path().extension() == ".apk") {
                  try {
                    auto message = bot->getApi().sendDocument(
                        tgTestGroupId,
                        TgBot::InputFile::fromFile(
                            entry.path().string(),
                            "application/vnd.android.package-archive"),
                        "",
                        "#" + Utils::getVersionCode(entry.path().string()) +
                            "v" + Utils::getVersionName(entry.path().string()));
                    try {
                      bot->getApi().pinChatMessage(tgTestGroupId,
                                                   message->messageId, true);
                    } catch (const std::exception &e) {
                      std::cout << "Pin error:" << e.what() << "\n";
                    }
                  } catch (const std::exception &e) {
                    std::cout << "Message send error:" << e.what() << "\n";
                  }
                }
              }

              Utils::execute("rm -r " + downloadPath);
            }
          }
        } else if (task->type == TASK_TYPE::BUILD) {
        }
      } catch (const std::exception &e) {
        std::cout << "Task error:" << e.what() << "\n";
        dbController.setTaskStatus(task->id, TASK_STATUS::CONFIRMED);
      }
    }

    {
      std::unique_lock<std::mutex> lock(taskMtx);
      if (resumeTaskThread && dbController.getConfirmedTask() == nullptr) {
        resumeTaskThread = false;
        taskCV.wait(lock, [] { return resumeTaskThread; });
      }
    }
  }
}

int main() {
  std::ifstream configFile("/buildroid/config.txt");
  // std::ifstream configFile("../config.txt");

  if (configFile.is_open()) {
    std::string line;
    while (std::getline(configFile, line)) {
      std::istringstream iss(line);
      std::string key, value;
      if (std::getline(iss, key, '=') && std::getline(iss, value)) {
        configMap[key] = value;
      }
    }
    configFile.close();
  } else {
    std::cerr << "Failed to open config file." << std::endl;
  }

  // git_libgit2_init();
  // GitManager::init(
  //     configMap["GIT_USERNAME"].c_str(),
  //     configMap["GIT_TOKEN"].c_str(),
  //     configMap["TAXI_REPO"].c_str(),
  //     (Utils::workDir + "/" + Utils::taxiPath).c_str());

  dbController.createTables();

  dbController.addListener(1, [](int action) {
    {
      std::unique_lock<std::mutex> lock(taskMtx);
      resumeTaskThread = true;
      taskCV.notify_one();
    }
  });

  bot = new Bot(configMap["BOT_TOKEN"]);

  std::thread tThread(tasksThread);
  tThread.detach();

  std::thread gWThread(gitWebhookThread);
  gWThread.detach();

  FragmentManager fragmentManager(bot);
  fragmentManager.setFragmentFactory(
      [](int fragmentId) -> std::shared_ptr<Fragment> {
        std::shared_ptr<BaseFragment> fragment = nullptr;
        switch (fragmentId) {
          case Fragments::LOGIN: {
            fragment = std::make_shared<LoginFragment>();
            break;
          }
          case Fragments::MAIN: {
            fragment = std::make_shared<MainFragment>();
            break;
          }
          case Fragments::TAXI: {
            fragment = std::make_shared<TaxiFragment>();
            break;
          }
          case Fragments::APP: {
            fragment = std::make_shared<AppFragment>();
            break;
          }
          case Fragments::BUILD_TYPE: {
            fragment = std::make_shared<BuildTypeFragment>();
            break;
          }
          case Fragments::NOTE: {
            fragment = std::make_shared<NoteFragment>();
            break;
          }
          case Fragments::CONFIRM: {
            fragment = std::make_shared<ConfirmFragment>();
            break;
          }
          default:
            fragment = std::make_shared<BaseFragment>(1);
        }

        fragment->setDBController(&dbController);
        return fragment;
      });

  // bot->getEvents().onCommand(
  //     {"start"},
  //     [&](TgBot::Message::Ptr message)
  //     {
  //         dbController.resetUser(message->from->id);
  // fragmentManager.onCommand(message);
  // });

  bot->getEvents().onNonCommandMessage(
      [&fragmentManager](Message::Ptr message) {
        //  fragmentManenvironmentager.onNonCommandMessage(message);
        if (message->text == "You alive ?")
          bot->getApi().sendMessage(message->chat->id, "think so", false,
                                    message->messageId);
      });

  // bot->getEvents().onCallbackQuery([&fragmentManager](CallbackQuery::Ptr
  // callbackQuery)
  //                                  {
  //                                  fragmentManager.onCallbackQuery(callbackQuery);
  //                                  });

  try {
    // webhook
     bot->getApi().deleteWebhook();
     bot->getApi().setWebhook("https://taxi-log.fast-taxi.uz/bot-tg-api/");
     TgWebhookTcpServer webhookServer(4000, "/", bot->getEventHandler());
     std::cout << "Bot working" << std::endl;
     webhookServer.start();

    // long poll
    // bot->getApi().deleteWebhook();
    // TgBot::TgLongPoll longPoll(*bot);
    // while (true) {
    //   std::cout << "Bot starting" << std::endl;
    //   longPoll.start();
    // }
  } catch (TgBot::TgException &e) {
    printf("error: %s\n", e.what());
  }

  printf("Exit bot\n");

  // git_libgit2_shutdown();

  printf("Exit server\n");

  return 0;
}