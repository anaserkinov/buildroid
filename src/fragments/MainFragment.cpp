#include "Fragments.hpp"

MainFragment::MainFragment()
    : BaseFragment(Fragments::MAIN){};

void MainFragment::onCreate(const Message::Ptr& lastMessage) {
    BaseFragment::onCreate(lastMessage);
    auto keyboard = std::make_shared<ReplyKeyboardMarkup>();
    keyboard->resizeKeyboard = true;
    keyboard->oneTimeKeyboard = true;
    sendMessage(
        lastMessage->chat->id,
        "Select 👁",
        false,
        0,
        createKeyboard(
            {
                {"Taxi 🚕",
                 "Bito 🧮"},
            },
            keyboard));
}

void MainFragment::onNonCommandMessage(const Message::Ptr& message) {
    if (message->text == "Bito 🧮") {
        dbController->selectProject(message->from->id, "bito");
        sendMessage(
            message->chat->id,
            "https://play.google.com/store/apps/details?id=uz.unical.bito.pro");
    } else if (message->text == "Taxi 🚕") {
        dbController->selectProject(message->from->id, "taxi");
        presentFragment(Fragments::TAXI, message);
    } else
    sendMessage(
        message->chat->id,
        "🧠"
    );
}
