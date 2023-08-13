#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <pthread.h>
#include <tgbot/tgbot.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

#include "DatabaseController.hpp"
#include "FragmentManager.hpp"
#include "Fragments.hpp"
#include "GitManager.hpp"

using namespace TgBot;

pthread_t thread;

void signalHandler(int s) {
    printf("SIGINT got\n");
    // listener.close().wait();
    pthread_join(thread, nullptr);
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

    pthread_create(&thread, nullptr, runListener, nullptr);

    git_libgit2_init();
    GitManager::init(
        configMap["GIT_USERNAME"].c_str(),
        configMap["GIT_TOKEN"].c_str(),
        configMap["TAXI_REPO"].c_str(),
        (Utils::workDir + "/" + Utils::taxiPath).c_str());

    TgBot::Bot bot(configMap["BOT_TOKEN"]);

    DatabaseController dbController;
    dbController.createTables();

    FragmentManager fragmentManager(&bot);
    fragmentManager.setFragmentFactory([&dbController](int fragmentId) -> std::shared_ptr<Fragment> {
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
            default:
                fragment = std::make_shared<BaseFragment>(1);
        }

        fragment->setDBController(&dbController);
        return fragment;
    });

    bot.getEvents().onCommand(
        {"start"},
        [&](TgBot::Message::Ptr message) {
            fragmentManager.onCommand(message);
        });

    bot.getEvents().onNonCommandMessage([&bot, &fragmentManager](Message::Ptr message) {
        fragmentManager.onNonCommandMessage(message);
    });

    signal(SIGINT, signalHandler);

    try {
        bot.getApi().deleteWebhook();

        // TgWebhookTcpServer webhookServer(8080, bot);
        // printf("Server starting\n");

        // bot.getApi().deleteWebhook();
        // bot.getApi().setWebhook("https://anasxonunical.jprq.live");
        // webhookServer.start();

        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }

    printf("Exit bot\n");

    pthread_join(thread, nullptr);
    git_libgit2_shutdown();

    printf("Exit server\n");

    return 0;
}