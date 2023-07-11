#include "Fragments.hpp"

LoginFragment::LoginFragment(): BaseFragment(Fragments::LOGIN){};

void LoginFragment::onCommand(const Message::Ptr& message){
    ReplyKeyboardMarkup::Ptr keyboard(new ReplyKeyboardMarkup);
    createKeyboard("Phone number", keyboard);
    getApi().sendMessage(
        message->chat->id,
        nullptr,
        false,
        0,
        keyboard
    );
}

void LoginFragment::onNonCommandMessage(const Message::Ptr& message) {
}
