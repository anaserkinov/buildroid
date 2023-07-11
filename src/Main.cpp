#include <tgbot/tgbot.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

#include "DatabaseController.hpp"
#include "FragmentManager.hpp"
#include "Fragments.hpp"

using namespace TgBot;

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

    TgBot::Bot bot(configMap["BOT_TOKEN"]);

    DatabaseController dbController;

    FragmentManager fragmentManager(&bot);
    fragmentManager.setFragmentFactory([&dbController](int fragmentId) -> std::shared_ptr<Fragment> {
        switch (fragmentId) {
        case Fragments::LOGIN: {
            auto fragment = std::make_shared<LoginFragment>();
            fragment->setDBController(&dbController);
            return fragment;
        }
        default:
            return std::make_shared<Fragment>(1);
        }
    });

    bot.getEvents().onCommand(
            {"start"},
            [&](TgBot::Message::Ptr message) {
                fragmentManager.onCommand(message);

                // std::cout << "onConmmad: " << message->text << "\n";
                // ReplyKeyboardMarkup::Ptr keyboardOneCol(new ReplyKeyboardMarkup);
                // std::vector<KeyboardButton::Ptr> row;
                // KeyboardButton::Ptr button(new KeyboardButton);
                // button->text = "Loy";
                // row.push_back(button);
                // keyboardOneCol->keyboard.push_back(row);
                // bot.getApi().sendMessage(
                //         message->chat->id,
                //         "Lll",
                //         false,
                //         0,
                //         keyboardOneCol);
            });

    bot.getEvents().onAnyMessage([&bot, &fragmentManager](Message::Ptr message) {
        // const std::string message = message->text;
        std::cout << "onAny: " << message->text << "\n";
    });

    bot.getEvents().onNonCommandMessage([&bot, &fragmentManager](Message::Ptr message) {
        // const std::string message = message->text;
        std::cout << message->text << "\n";
        if (message->contact != nullptr) {
            std::cout << message->contact->phoneNumber << "\n";
        }
    });

    signal(SIGINT, [](int s) {
        printf("SIGINT got\n");
        exit(0);
    });

    try {
        bot.getApi().deleteWebhook();

        std::cout << bot.getApi().getMe()->firstName;

        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }

    return 0;
}