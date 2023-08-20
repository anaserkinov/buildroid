#include <algorithm>

#include "Fragments.hpp"

LoginFragment::LoginFragment()
    : BaseFragment(Fragments::LOGIN) {
    admins.emplace_back("998941533373");
    admins.emplace_back("77713128955");
    admins.emplace_back("998993212503");
    admins.emplace_back("998910041156");
    admins.emplace_back("998951045011");
    admins.emplace_back("998933893700");
    admins.emplace_back("998909809606");
};

void LoginFragment::onCommand(const Message::Ptr& message) {
    auto keyboard = std::make_shared<ReplyKeyboardMarkup>();
    keyboard->resizeKeyboard = true;
    auto button = std::make_shared<KeyboardButton>();
    button->requestContact = true;
    button->text = "Phone number";
    sendMessage(
        message->chat->id,
        "Send your phone number",
        false,
        0,
        addButton(keyboard, button));
}

void LoginFragment::onNonCommandMessage(const Message::Ptr& message) {
    // if (message->contact != nullptr && message->from->id == message->contact->userId) {
    if (message->contact != nullptr) {
        auto admin = std::find(admins.begin(), admins.end(), message->contact->phoneNumber);
        if (admin != admins.end()) {
            auto user = message->from;
            std::cout << "userId in login: " << user->id << "\n";
            dbController->insertUser(
                user->id,
                user->firstName,
                user->lastName,
                message->contact->phoneNumber,
                user->username);

            sendMessage(
                message->chat->id,
                "Oo you, " + message->from->firstName + " 🫵, again",
                false,
                0,
                std::make_shared<ReplyKeyboardRemove>());
            presentFragment(Fragments::MAIN, message);
            return;
        }
    }
    sendMessage(
        message->chat->id,
        "Access denied 🚫");
}