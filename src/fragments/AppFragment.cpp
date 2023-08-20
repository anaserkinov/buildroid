#include "Fragments.hpp"
#include "utils.hpp"

AppFragment::AppFragment()
    : BaseFragment(Fragments::APP){};

void AppFragment::onCreate(const Message::Ptr& lastMessage) {
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
             {"All"},
             {"salamtaxi",
              "hamkortaxi"},
             {"startaxi",
              "fivecitytaxi"},
             {"demotaxi",
              "unicaltaxi"},
             {"expresstaxi"}},
            keyboard));
}

void AppFragment::onNonCommandMessage(const Message::Ptr& message) {
    auto text = message->text;
    Utils::clearStringFromSticker(text);
    std::cout << text;
    if (text == "Back") {
        presentFragment(Fragments::BUILD_TYPE, message);
    } else {
        if (text == "All" || Utils::isFolderExists(Utils::workDir + "/" + Utils::taxiPath + "/new/apps/" + text)) {
            dbController->selectApp(
                message->from->id,
                text);
        } else
            sendMessage(
                message->chat->id,
                "🧠");
    }
}