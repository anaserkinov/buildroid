#include "Fragments.hpp"

MainFragment::MainFragment()
    : BaseFragment(Fragments::MAIN){};

void MainFragment::onCreate(int16_t type, const std::shared_ptr<void>& data) {
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
        presentFragment(Fragments::TAXI, Fragment::MESSAGE, message);
    } else
        sendMessage(
            message->chat->id,
            "🧠");
}
