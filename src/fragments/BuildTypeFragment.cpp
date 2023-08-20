#include "Fragments.hpp"
#include "utils.hpp"

BuildTypeFragment::BuildTypeFragment()
    : BaseFragment(Fragments::BUILD_TYPE){};

void BuildTypeFragment::onCreate(const Message::Ptr& lastMessage) {
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
            {{"<Back 🇺🇿"},
             {"Publish ☢"},
             {"Release 🔐",
              "Debug 🐞"}},
            keyboard));
}

void BuildTypeFragment::onNonCommandMessage(const Message::Ptr& message) {
    auto text = message->text;
    Utils::clearStringFromSticker(text);
    std::cout << text;
    if (text == "Back") {
        presentFragment(Fragments::TAXI, message);
    } else {
        if (text == "Publish" || text == "Release" || text == "Debug") {
            dbController->selectBuildType(
                message->from->id,
                text);
            presentFragment(Fragments::APP, message);
        } else
            sendMessage(
                message->chat->id,
                "🧠");
    }
}