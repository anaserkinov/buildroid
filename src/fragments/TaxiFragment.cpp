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
        {"<Back 🇺🇿"});
    buttons.push_back(
        {"Sync ♻️"});
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
        "Select 👁",
        false,
        0,
        createKeyboard(
            buttons,
            keyboard));
}

void TaxiFragment::onNonCommandMessage(const Message::Ptr& message) {
    if (message->text == "<Back 🇺🇿") {
        presentFragment(Fragments::MAIN, message);
    } else if (message->text == "Sync ♻️") {
        (GitManager()).fetch((Utils::workDir + "/" + Utils::taxiPath).c_str());
        onCreate(message);
    } else {
        std::string branch = message->text;

        auto gitManager = GitManager();
        std::vector<std::string> branches;
        gitManager.getBranches((Utils::workDir + "/" + Utils::taxiPath).c_str(), branches);

        auto exists = std::find(branches.begin(), branches.end(), branch);

        if (exists != branches.end()) {
            dbController->selectBranch(message->from->id, branch);
            presentFragment(Fragments::BUILD_TYPE, message);
        } else
            sendMessage(
                message->chat->id,
                "🧠");
    }
}