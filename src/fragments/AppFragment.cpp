#include "Fragments.hpp"
#include "utils.hpp"

AppFragment::AppFragment()
    : BaseFragment(Fragments::APP){};

void AppFragment::onCreate(int16_t type, const std::shared_ptr<void>& data) {
    BaseFragment::onCreate(type, data);
    Message::Ptr lastMessage = std::reinterpret_pointer_cast<Message>(data);
    auto keyboard = std::make_shared<ReplyKeyboardMarkup>();
    keyboard->resizeKeyboard = true;
    keyboard->oneTimeKeyboard = true;

    std::vector<KeyboardButton::Ptr> fRow;
    auto button = std::make_shared<KeyboardButton>();
    button->text = "<Back 🇺🇿";
    fRow.push_back(button);
    keyboard->keyboard.push_back(fRow);

    std::vector<KeyboardButton::Ptr> sRow;
    button = std::make_shared<KeyboardButton>();
    button->text = "All";
    sRow.push_back(button);
    keyboard->keyboard.push_back(sRow);


    sendMessage(
        lastMessage->chat->id,
        "Select 👁",
        false,
        0,
        createKeyboard(
            Utils::getTaxiApps(),
            keyboard,
            2));
}

void AppFragment::onNonCommandMessage(const Message::Ptr& message) {
    auto text = message->text;
    Utils::clearStringFromSticker(text);
    std::cout << text;
    if (text == "Back") {
        presentFragment(Fragments::TAXI, Fragment::MESSAGE, message);
    } else {
        if (text == "All" || Utils::isFolderExists(Utils::workDir + "/" + Utils::taxiPath + "/apps/" + text)) {
            dbController->selectApp(
                message->from->id,
                text);
            presentFragment(Fragments::BUILD_TYPE, Fragment::MESSAGE, message);
        } else
            sendMessage(
                message->chat->id,
                "🧠");
    }
}