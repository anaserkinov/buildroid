#include "Fragments.hpp"
#include "GitManager.hpp"
#include "gitty.hpp"

TaxiFragment::TaxiFragment()
    : BaseFragment(Fragments::TAXI){};

void TaxiFragment::onCreate(const Message::Ptr& lastMessage) {
    std::vector<std::string> branches;

    auto gitManager = GitManager();
    gitManager.getBranches((Utils::workDir + "/" + Utils::taxiPath).c_str(), branches);

    std::vector<std::vector<std::string>> buttons;
    buttons.push_back(
        {"Sync"});
    placeKeyboards(
        branches,
        buttons,
        2);

    BaseFragment::onCreate(lastMessage);
    auto keyboard = std::make_shared<ReplyKeyboardMarkup>();
    keyboard->resizeKeyboard = true;
    keyboard->oneTimeKeyboard = true;
    sendMessage(
        lastMessage->chat->id,
        "Select branch",
        false,
        0,
        createKeyboard(
            buttons,
            keyboard));
}

void TaxiFragment::onNonCommandMessage(const Message::Ptr& message) {
    if (message->text == "Sync") {
        sendMessage(
            message->chat->id,
            "https://play.google.com/store/apps/details?id=uz.unical.bito.pro");
    } else {



    }
}
