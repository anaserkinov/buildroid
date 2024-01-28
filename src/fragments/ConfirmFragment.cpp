#include "Fragments.hpp"
#include "utils.hpp"

ConfirmFragment::ConfirmFragment()
    : BaseFragment(Fragments::CONFIRM){};

void ConfirmFragment::onCreate(int16_t type, const std::shared_ptr<void>& data) {
    Message::Ptr message = std::reinterpret_pointer_cast<Message>(data);

    std::unique_ptr task = dbController->getTask(
        dbController->getCurrentTaskId(message->from->id));

    if (task == nullptr)
        sendMessage(
            message->chat->id,
            "Task not found");
    else {
        BaseFragment::onCreate(type, data);

        dbController->setTaskStatus(
            task->id,
            TASK_STATUS::NEW);

        task->status = TASK_STATUS::NEW;

        auto keyboard = std::make_shared<InlineKeyboardMarkup>();
        auto removeMesssage = sendMessage(
            message->chat->id,
            "Wait please",
            false,
            0,
            std::make_shared<ReplyKeyboardRemove>());
        deleteMessage(
            message->chat->id,
            removeMesssage->messageId);

        Message::Ptr response = sendMessage(
            message->chat->id,
            Utils::getTaskInfoText(std::move(task)),
            false,
            0,
            createInlineKeyboard(
                {{"Edit✏️", "edit_task", "Cancel❌", "delete_task"},
                 {"Confirm✅", "confirm_task"}},
                keyboard),
            "html");
        dbController->setTaskMessageId(
            task->id,
            response->chat->id,
            response->messageId);
    }
}

void ConfirmFragment::onCallbackQuery(const CallbackQuery::Ptr& callbackQuery) {
    std::unique_ptr task = dbController->getTask(
        dbController->getTaskId(
            callbackQuery->message->chat->id,
            callbackQuery->message->messageId));

    if (task == nullptr)
        sendMessage(
            callbackQuery->message->chat->id,
            "Task not found");
    else {
        if (task->status == TASK_STATUS::NEW) {
            if (callbackQuery->data == "edit_task") {
                dbController->setTaskStatus(
                    task->id,
                    TASK_STATUS::CREATED);
                dbController->setTaskMessageId(
                    task->id,
                    -1,
                    -1);
                editMessageText(
                    callbackQuery->message->text,
                    callbackQuery->message->chat->id,
                    callbackQuery->message->messageId);
                presentFragment(Fragments::BUILD_TYPE, Fragment::CALLBACK_QUERY, callbackQuery);
            } else if (callbackQuery->data == "delete_task") {
                dbController->deleteTask(task->id);
                editMessageText(
                    callbackQuery->message->text,
                    callbackQuery->message->chat->id,
                    callbackQuery->message->messageId);
                answerCallbackQuery(callbackQuery->id, "Task cancelled");
                presentFragment(Fragments::MAIN, Fragment::CALLBACK_QUERY, callbackQuery);
            } else if (callbackQuery->data == "confirm_task") {
                task->status = TASK_STATUS::CONFIRMED;
                auto message = editMessageText(
                    Utils::getTaskInfoText(std::move(task)),
                    callbackQuery->message->chat->id,
                    callbackQuery->message->messageId,
                    "",
                    "html");
                    
                dbController->setTaskMessageId(
                    task->id,
                    message->chat->id,
                    message->messageId);
                dbController->setTaskStatus(
                    task->id,
                    TASK_STATUS::CONFIRMED);
                presentFragment(Fragments::MAIN, Fragment::CALLBACK_QUERY, callbackQuery);
            }
        }
        answerCallbackQuery(callbackQuery->id);
    }
}