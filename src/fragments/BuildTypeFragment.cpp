#include "Fragments.hpp"
#include "utils.hpp"

BuildTypeFragment::BuildTypeFragment()
    : BaseFragment(Fragments::BUILD_TYPE){};

void BuildTypeFragment::onCreate(int16_t type, const std::shared_ptr<void>& data) {
    BaseFragment::onCreate(type, data);
    int64_t chatId;
    if (type == Fragment::MESSAGE)
        chatId = std::reinterpret_pointer_cast<Message>(data)->chat->id;
    else
        chatId = std::reinterpret_pointer_cast<CallbackQuery>(data)->message->chat->id;
    auto keyboard = std::make_shared<ReplyKeyboardMarkup>();
    keyboard->resizeKeyboard = true;
    keyboard->oneTimeKeyboard = true;
    sendMessage(
        chatId,
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
        presentFragment(Fragments::APP, Fragment::MESSAGE, message);
    } else {
        if (text == "Publish" || text == "Release" || text == "Debug") {
            if (text == "Publish") {
                sendMessage(
                    message->chat->id,
                    "Not yet available");
                return;
            }

            dbController->selectBuildType(
                message->from->id,
                text);
            presentFragment(Fragments::CONFIRM, Fragment::MESSAGE, message);
        } else
            sendMessage(
                message->chat->id,
                "🧠");
    }
}