#include "Fragments.hpp"

MainFragment::MainFragment()
    : BaseFragment(Fragments::MAIN){};

void MainFragment::onCreate(const Message::Ptr& lastMessage) {
    dbController->updateFragmentState(lastMessage->from->id, fragmentId);
    auto keyboard = std::make_shared<ReplyKeyboardMarkup>();
    keyboard->resizeKeyboard = true;
    keyboard->oneTimeKeyboard = true;
    sendMessage(
        lastMessage->chat->id,
        "Select project",
        false,
        0,
        createKeyboard(
            {
                {"Taxi",
                 "Bito"},
            },
            keyboard));
}

void MainFragment::onNonCommandMessage(const Message::Ptr& message) {
    if (message->text == "Bito") {
        sendMessage(
            message->chat->id,
            "https://play.google.com/store/apps/details?id=uz.unical.bito.pro");
    } else if (message->text == "Taxi") {
        presentFragment(Fragments::TAXI, message);
    }
}
