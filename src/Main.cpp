#include <cpprest/http_listener.h>
#include <cpprest/json.h>
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

namespace fs = std::filesystem;

TgBot::Bot* bot = nullptr;
DatabaseController dbController;

std::string lastUsedBranch = "";

std::mutex docekrMtx;
std::condition_variable dockerCV;
bool resumeDCThread = true;

std::string getContainerStatus(const std::string& containerName) {
    std::string command = "docker inspect --format '{{.State.Status}}' " + containerName;

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "Error executing command." << std::endl;
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

void signalHandler(int s) {
    printf("SIGINT got\n");
    // listener.close().wait();
    // pthread_join(thread, nullptr);
    exit(0);
};

void* runListener(void* arg) {
    // web::http::experimental::listener::http_listener listener("http://localhost:8080/");

    // listener.support(web::http::methods::POST, [](web::http::http_request request) {
    //     // web::json::value response;
    //     // response["message"] = web::json::value::string("Hello, World!");

    //     // web::http::http_response httpResponse(web::http::status_codes::OK);
    //     // httpResponse.headers().add(U("Content-Type"), U("application/json"));
    //     // httpResponse.set_body(response);

    //     // request.reply(httpResponse);
    //     std::cout<<request.body().is_valid();
    // });

    // listener.open().then([]() {
    //                    std::cout << "Listening on http://localhost:8080/" << std::endl;
    //                })
    //         .wait();

    // listener.close().wait();

    return nullptr;
}

void dockerThread() {
    while (true) {
        std::unique_ptr<Task> task = dbController.getConfirmedTask();

        std::cout << "thread running \n";

        if (task != nullptr) {
            try {
                dbController.setTaskStatus(
                    task->id,
                    TASK_STATUS::IN_PROGRESS);
                task->status = TASK_STATUS::IN_PROGRESS;

                bot->getApi().editMessageText(
                    Utils::getTaskInfoText(task),
                    task->charId,
                    task->messageId,
                    "",
                    "html");

                GitManager gitManager;
                gitManager.checkout(
                    Utils::workDir + "/" + Utils::taxiPath,
                    task->branch);

                {
                    std::ofstream localProperties(Utils::workDir + "/" + Utils::taxiPath + "/" + "local.properties");
                    localProperties << "sdk.dir=/usr/local/android-sdk-linux";
                    localProperties.close();
                }

                std::string containerStatus = getContainerStatus("taxi_container");
                std::cout << "docker container status: " << containerStatus << "\n";
                if (containerStatus != "running") {
                    int result = system("docker start taxi_container");
                    if (result == 0) {
                        std::cout << "Taxi container has been started\n";
                    } else {
                        std::cout << "Container couldn't be started\n";
                    }
                }

                std::string command = "docker exec -t taxi_container /bin/bash -c ";

                command += "\"rm -rf /home/source/docker/build/outputs/publish && ";
                command += "mkdir -p /home/source/docker/build/outputs/publish && ";
                command += "rm -rf /home/source/docker/build/outputs/release && ";
                command += "mkdir -p /home/source/docker/build/outputs/release && ";
                command += "rm -rf /home/source/docker/build/outputs/debug && ";
                command += "mkdir -p /home/source/docker/build/outputs/debug && ";
                command += "rm -rf /home/gradle/unicaltaxi-driver && ";
                command += "cp -R /home/source/. /home/gradle/unicaltaxi-driver && ";
                command += "cd /home/gradle/unicaltaxi-driver";

                if (lastUsedBranch != task->branch) {
                    lastUsedBranch = task->branch;
                    command += " && find . -type d -path '*/src/*' -prune -o -name 'build' -type d -exec rm -rf {} +";
                    command += " && ./gradlew clean";
                    // command += " && ./gradlew build --refresh-dependencies";
                }

                // assembleStandaloneDebug
                // assembleDebug
                // assembleRelease
                // bundleRelease

                std::string buildCommand;
                std::string copyOuputCommand;

                {
                    std::vector<std::string> apps;

                    if (task->app == "All") {
                        std::vector<std::string> allApps = Utils::getTaxiApps();
                        apps.assign(allApps.begin(), allApps.end());
                    } else {
                        apps.push_back(task->app);
                    }

                    if (task->buildType == "publish") {
                        for (std::string app : apps) {
                            buildCommand += "gradle :apps:" + app + ":bundleStoreRelease && ";
                            copyOuputCommand += "cp -R /home/gradle/unicaltaxi-driver/apps/" +
                                                app +
                                                "/store/release/. /home/source/docker/build/outputs/publish && ";
                        }
                    } else if (task->buildType == "release") {
                        for (std::string app : apps) {
                            buildCommand += "gradle :apps:" + app + ":assembleStoreRelease && ";
                            copyOuputCommand += "cp -R /home/gradle/unicaltaxi-driver/apps/" +
                                                app +
                                                "/build/outputs/apk/store/release/. /home/source/docker/build/outputs/release && ";
                        }
                    } else {
                        for (std::string app : apps) {
                            buildCommand += "gradle :apps:" + app + ":assembleStoreDebug && ";
                            copyOuputCommand += "cp -R /home/gradle/unicaltaxi-driver/apps/" +
                                                app +
                                                "/build/outputs/apk/store/debug/. /home/source/docker/build/outputs/debug && ";
                        }
                    }

                    buildCommand.erase(buildCommand.length() - 4, 4);
                    copyOuputCommand.erase(copyOuputCommand.length() - 4, 4);
                }

                command += " && " + buildCommand;
                command += " && " + copyOuputCommand;

                command += "\"";

                Utils::execute(command);

                dbController.setTaskStatus(
                    task->id,
                    TASK_STATUS::COMPLETED);

                task->status = TASK_STATUS::COMPLETED;

                bot->getApi().editMessageText(
                    Utils::getTaskInfoText(task),
                    task->charId,
                    task->messageId,
                    "",
                    "html");

                if (task->buildType == "publish") {
                    for (const auto& entry : fs::recursive_directory_iterator(fs::current_path().string() + "/" + Utils::workDir + "/" + Utils::taxiPath + "/docker/build/outputs/publish")) {
                        if (entry.is_regular_file() && entry.path().extension() == ".aab") {
                            bot->getApi().sendDocument(
                                task->charId,
                                InputFile::fromFile(entry.path().string(), "application/x-authorware-bin"));
                        }
                    }
                } else if (task->buildType == "release") {
                    for (const auto& entry : fs::recursive_directory_iterator(fs::current_path().string() + "/" + Utils::workDir + "/" + Utils::taxiPath + "/docker/build/outputs/release")) {
                        if (entry.is_regular_file() && entry.path().extension() == ".apk") {
                            bot->getApi().sendDocument(
                                task->charId,
                                InputFile::fromFile(entry.path().string(), "application/vnd.android.package-archive"));
                        }
                    }
                } else {
                    for (const auto& entry : fs::recursive_directory_iterator(fs::current_path().string() + "/" + Utils::workDir + "/" + Utils::taxiPath + "/docker/build/outputs/debug")) {
                        if (entry.is_regular_file() && entry.path().extension() == ".apk") {
                            bot->getApi().sendDocument(
                                task->charId,
                                InputFile::fromFile(entry.path().string(), "application/vnd.android.package-archive"));
                        }
                    }
                }

            } catch (const std::exception& e) {
                std::cerr << e.what() << '\n';
                dbController.setTaskStatus(
                    task->id,
                    TASK_STATUS::CONFIRMED);
            }
        }

        {
            std::unique_lock<std::mutex> lock(docekrMtx);
            if (resumeDCThread && dbController.getConfirmedTask() == nullptr) {
                resumeDCThread = false;
                dockerCV.wait(lock, [] { return resumeDCThread; });
            }
        }
    }
}

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

bool checkIfDCImageExists() {
    FILE* pipe = popen("docker images --format \"{{.Repository}}\"", "r");

    if (!pipe) {
        std::cerr << "Error: Unable to run the Docker command." << std::endl;
        return 1;
    }

    char buffer[128];

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        buffer[strcspn(buffer, "\n")] = '\0';
        if (std::string(buffer) == "taxi_image") {
            pclose(pipe);
            return true;
        }
    }

    pclose(pipe);

    return false;
}

bool checkIfDCContainerExists() {
    FILE* pipe = popen("docker ps -a --format '{{.Names}}'", "r");

    if (!pipe) {
        std::cerr << "Error: Unable to run the Docker command." << std::endl;
        return 1;
    }

    char buffer[128];

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        buffer[strcspn(buffer, "\n")] = '\0';
        if (std::string(buffer) == "taxi_container") {
            pclose(pipe);
            return true;
        }
    }

    pclose(pipe);

    return false;
}

int main() {
    std::ifstream configFile("../config.txt");
    std::unordered_map<std::string, std::string> configMap;

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

    git_libgit2_init();
    GitManager::init(
        configMap["GIT_USERNAME"].c_str(),
        configMap["GIT_TOKEN"].c_str(),
        configMap["TAXI_REPO"].c_str(),
        (Utils::workDir + "/" + Utils::taxiPath).c_str());

    if (checkIfDCImageExists()) {
        std::cout << "Taxi image already exists\n";
    } else {
        int result = system(
            "docker build -t "
            "taxi_image "
            "-f workdir/unicaltaxi-driver/Dockerfile .");
        if (result == 0) {
            std::cout << "Taxi image has been created\n";
        } else {
            std::cout << "Creating image failed\n";
        }
    }

    if (checkIfDCContainerExists()) {
        std::cout << "Taxi container already exists\n";
    } else {
        const char* relativePath = "workdir/unicaltaxi-driver";
        std::filesystem::path absolutePath = std::filesystem::absolute(relativePath);

        std::string cmd = "docker run -d -v " + absolutePath.string() + ":/home/source --name taxi_container taxi_image";

        int result = system(cmd.c_str());
        if (result == 0) {
            std::cout << "Taxi container has been created\n";
        } else {
            std::cout << "Taxi container has been created\n";
        }
    }

    if (getContainerStatus("taxi_container") == "running") {
        int result = system("docker stop taxi_container");
        if (result == 0) {
            std::cout << "Taxi container has been stopped\n";
        } else {
            std::cout << "Container couldn't be stopped\n";
        }
    }

    dbController.createTables();

    dbController.addListener(1, [](int action) {
        std::cout << "confirmed"
                  << "\n";
        {
            std::unique_lock<std::mutex> lock(docekrMtx);
            resumeDCThread = true;
            dockerCV.notify_one();
        }
    });

    bot = new Bot(configMap["BOT_TOKEN"]);

    std::thread dcThread(dockerThread);
    dcThread.detach();

    FragmentManager fragmentManager(bot);
    fragmentManager.setFragmentFactory([](int fragmentId) -> std::shared_ptr<Fragment> {
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

    bot->getEvents().onCommand(
        {"start"},
        [&](TgBot::Message::Ptr message) {
            dbController.resetUser(message->from->id);
            fragmentManager.onCommand(message);
        });

    bot->getEvents().onNonCommandMessage([&fragmentManager](Message::Ptr message) {
        fragmentManager.onNonCommandMessage(message);
    });

    bot->getEvents().onCallbackQuery([&fragmentManager](CallbackQuery::Ptr callbackQuery) {
        fragmentManager.onCallbackQuery(callbackQuery);
    });

    // signal(SIGINT, signalHandler);

    try {
        bot->getApi().deleteWebhook();

        // TgWebhookTcpServer webhookServer(8080, bot);
        // printf("Server starting\n");

        // bot.getApi().deleteWebhook();
        // bot.getApi().setWebhook("https://anasxonunical.jprq.live");
        // webhookServer.start();

        TgBot::TgLongPoll longPoll(*bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }

    printf("Exit bot\n");

    git_libgit2_shutdown();

    printf("Exit server\n");

    return 0;
}