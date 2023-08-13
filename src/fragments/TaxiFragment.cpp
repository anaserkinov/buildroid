#include "Fragments.hpp"

TaxiFragment::TaxiFragment()
    : BaseFragment(Fragments::TAXI){};

void TaxiFragment::onCreate(const Message::Ptr& lastMessage) {
    // std::vector<std::vector<std::string>> buttons;
    // buttons.push_back(
    //     {"Sync"});
    // placeKeyboards(
    //     branches,
    //     buttons,
    //     2);

    BaseFragment::onCreate(lastMessage);
    auto keyboard = std::make_shared<ReplyKeyboardMarkup>();
    keyboard->resizeKeyboard = true;
    keyboard->oneTimeKeyboard = true;
    // sendMessage(
    //     lastMessage->chat->id,
    //     "Select app",
    //     false,
    //     0,
    //     createKeyboard(
    //         {},
    //         keyboard));
}

void TaxiFragment::onNonCommandMessage(const Message::Ptr& message) {
    if (message->text == "Add new") {
    
    } else {
        
    }
}
