#include "Fragments.hpp"
#include "GitManager.hpp"
#include "gitty.hpp"

TaxiFragment::TaxiFragment()
    : BaseFragment(Fragments::TAXI){};

void TaxiFragment::onCreate(int16_t type, const std::shared_ptr<void>& data) {
    Message::Ptr lastMessage = std::reinterpret_pointer_cast<Message>(data);

    std::vector<std::string> branches;

    auto gitManager = GitManager();
    gitManager.getBranches(Utils::workDir + "/" + Utils::taxiPath, branches);

    std::vector<std::vector<std::string>> buttons;
    buttons.push_back(
        {"<Back 🇺🇿"});
    buttons.push_back(
        {"Sync ♻️"});
    placeKeyboards(
        branches,
        buttons,
        2);

    BaseFragment::onCreate(type, data);
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
        presentFragment(Fragments::MAIN, Fragment::MESSAGE, message);
    } else if (message->text == "Sync ♻️") {
        (GitManager()).fetch(Utils::workDir + "/" + Utils::taxiPath);
        onCreate(Fragment::MESSAGE, message);
    } else {
        std::string branch = message->text;

        auto gitManager = GitManager();
        std::vector<std::string> branches;
        gitManager.getBranches(Utils::workDir + "/" + Utils::taxiPath, branches);

        auto exists = std::find(branches.begin(), branches.end(), branch);

        if (exists != branches.end()) {
            dbController->selectBranch(message->from->id, branch);
            presentFragment(Fragments::APP, Fragment::MESSAGE, message);
        } else
            sendMessage(
                message->chat->id,
                "🧠");
    }
}