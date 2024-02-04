#include "Fragments.hpp"
#include "utils.hpp"

NoteFragment::NoteFragment()
    : BaseFragment(Fragments::NOTE){};

void NoteFragment::onCreate(int16_t type, const std::shared_ptr<void>& data) {
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
        "Send a title ✏️",
        false,
        0,
        createKeyboard(
            {{"<Back 🇺🇿"},
             {"Skip>"}},
            keyboard));
}

void NoteFragment::onNonCommandMessage(const Message::Ptr& message) {
    auto text = message->text;
    Utils::clearStringFromSticker(text);
    if (text == "Back") {
        presentFragment(Fragments::BUILD_TYPE, Fragment::MESSAGE, message);
    } else {
        if (text != "Skip")
            dbController->setTaskTitle(
                message->from->id,
                text);
        presentFragment(Fragments::CONFIRM, Fragment::MESSAGE, message);
    }
}