#include "DatabaseController.hpp"

#include "Fragments.hpp"
#include "utils.hpp"

DatabaseController::DatabaseController() {
}

void DatabaseController::createTables() {
    try {
        MainDatabase::getDB().executeFast(
                                 "CREATE TABLE IF NOT EXISTS users("
                                 "id INTEGER NOT NULL PRIMARY KEY,"
                                 "firstName TEXT,"
                                 "lastName TEXT,"
                                 "phoneNumber TEXT,"
                                 "userName TEXT,"
                                 "fragmentId INTEGER"
                                 ")")
            ->stepThis()
            .dispose();
        MainDatabase::getDB().executeFast(
                                 "CREATE TABLE IF NOT EXISTS tasks("
                                 "id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                                 "userId INTEGER,"
                                 "project TEXT,"
                                 "branch TEXT,"
                                 "app TEXT,"
                                 "buildType TEXT,"
                                 "title TEXT,"
                                 "status INTEGER,"
                                 "errorCode INTEGER,"
                                 "chatId INTEGER,"
                                 "messageId INTEGER,"
                                 "createdAt INTEGER,"
                                 "startedAt INTEGER,"
                                 "completedAt INTEGER"
                                 ")")
            ->stepThis()
            .dispose();
    } catch (const std::exception& e) {
        printf(e.what());
        throw e;
    }
}

void DatabaseController::addListener(int id, const Callback& callback) {
    mListeners.push_back(std::pair(id, callback));
}

void DatabaseController::removeListener(int id) {
    std::remove_if(
        mListeners.begin(),
        mListeners.end(),
        [&id](const auto& e) {
            return e.first == id;
        });
}

void DatabaseController::resetUser(int64_t id) {
    try {
        auto preparedS = MainDatabase::getDB().executeFast("UPDATE users SET fragmentId = ? WHERE id = ?");

        preparedS->bindInt32(1, Fragments::LOGIN);
        preparedS->bindInt64(2, id);

        preparedS->step();
        preparedS->dispose();
    } catch (const std::exception& e) {
        printf(e.what());
    }
}

void DatabaseController::insertUser(
    int64_t id,
    std::string firstName,
    std::string lastName,
    std::string phoneNumber,
    std::string userName) {
    try {
        auto preparedS = MainDatabase::getDB().executeFast(
            "REPLACE INTO users VALUES(?,?,?,?,?,?)");

        preparedS->requery();
        preparedS->bindInt64(1, id);
        preparedS->bindString(2, firstName);
        preparedS->bindString(3, lastName);
        preparedS->bindString(4, phoneNumber);
        preparedS->bindString(5, userName);
        preparedS->bindInt32(6, Fragments::LOGIN);

        preparedS->step();
        preparedS->dispose();
    } catch (const std::exception& e) {
        printf(e.what());
    }
}

void DatabaseController::updateFragmentState(
    int64_t id,
    int fragmentId) {
    try {
        auto preparedS = MainDatabase::getDB().executeFast("UPDATE users SET fragmentId = ? WHERE id = ?");

        preparedS->bindInt32(1, fragmentId);
        preparedS->bindInt64(2, id);

        preparedS->step();
        preparedS->dispose();
    } catch (const std::exception& e) {
        printf(e.what());
    }
}

int32_t DatabaseController::getCurrentTaskId(int64_t userId) {
    try {
        List<Object> args = {userId, TASK_STATUS::CREATED};
        CursorWrapper cursor = CursorWrapper(MainDatabase::getDB().queryFinalized("SELECT id FROM tasks WHERE userId = ? AND status = ? LIMIT 1", args));

        if (cursor.ptr->next())
            return cursor.ptr->longValue(0);

    } catch (const std::exception& e) {
        printf(e.what());
    }
    return -1;
}

int32_t DatabaseController::getTaskId(int64_t chatId, int64_t messageId) {
    try {
        List<Object> args = {chatId, messageId};
        CursorWrapper cursor = CursorWrapper(MainDatabase::getDB().queryFinalized("SELECT id FROM tasks WHERE chatId = ? AND messageId = ? LIMIT 1", args));

        if (cursor.ptr->next())
            return cursor.ptr->longValue(0);

    } catch (const std::exception& e) {
        printf(e.what());
    }
    return -1;
}

std::unique_ptr<Task> DatabaseController::getTask(int32_t taskId) {
    try {
        List<Object> args = {taskId};
        CursorWrapper cursor = CursorWrapper(MainDatabase::getDB().queryFinalized("SELECT * FROM tasks WHERE id = ?", args));

        if (cursor.ptr->next())
            return std::make_unique<Task>(
                Task{
                    cursor.ptr->longValue(0),
                    cursor.ptr->longValue(1),
                    cursor.ptr->stringValue(2),
                    cursor.ptr->stringValue(3),
                    cursor.ptr->stringValue(4),
                    cursor.ptr->stringValue(5),
                    cursor.ptr->stringValue(6),
                    cursor.ptr->intValue(7),
                    cursor.ptr->intValue(8),
                    cursor.ptr->longValue(9),
                    cursor.ptr->longValue(10)});

    } catch (const std::exception& e) {
        printf(e.what());
    }
    return nullptr;
}

std::unique_ptr<Task> DatabaseController::getConfirmedTask() {
    try {
        List<Object> args = {TASK_STATUS::CONFIRMED};
        CursorWrapper cursor = CursorWrapper(MainDatabase::getDB().queryFinalized("SELECT * FROM tasks WHERE status = ?", args));

        if (cursor.ptr->next())
            return std::make_unique<Task>(
                Task{
                    cursor.ptr->longValue(0),
                    cursor.ptr->longValue(1),
                    cursor.ptr->stringValue(2),
                    cursor.ptr->stringValue(3),
                    cursor.ptr->stringValue(4),
                    cursor.ptr->stringValue(5),
                    cursor.ptr->stringValue(6),
                    cursor.ptr->intValue(7),
                    cursor.ptr->intValue(8),
                    cursor.ptr->longValue(9),
                    cursor.ptr->longValue(10)});

    } catch (const std::exception& e) {
        printf(e.what());
    }
    return nullptr;
}

void DatabaseController::selectProject(
    int64_t userId,
    std::string projectName) {
    try {
        int32_t userTaskId = getCurrentTaskId(userId);
        if (userTaskId == -1) {
            auto preparedS = MainDatabase::getDB().executeFast(
                "REPLACE INTO tasks VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?)");

            preparedS->requery();
            preparedS->bindInt64(2, userId);
            preparedS->bindString(7, "");
            preparedS->bindInt32(8, TASK_STATUS::CREATED);
            preparedS->bindInt32(9, -1);
            preparedS->bindInt64(10, -1);
            preparedS->bindInt64(11, -1);
            preparedS->bindInt64(12, -1);
            preparedS->bindInt64(13, -1);
            preparedS->bindInt64(14, -1);

            userTaskId = preparedS->step(MainDatabase::getDB());
            preparedS->dispose();
        }

        auto preparedS = MainDatabase::getDB().executeFast("UPDATE tasks SET project = ? WHERE id = ?");

        preparedS->bindString(1, projectName);
        preparedS->bindInt64(2, userTaskId);

        preparedS->step();
        preparedS->dispose();
    } catch (const std::exception& e) {
        printf(e.what());
    }
}

void DatabaseController::selectBranch(
    int64_t userId,
    std::string branchName) {
    try {
        auto preparedS = MainDatabase::getDB().executeFast("UPDATE tasks SET branch = ? WHERE userId = ? AND status = ?");

        preparedS->bindString(1, branchName);
        preparedS->bindInt64(2, userId);
        preparedS->bindInt32(3, TASK_STATUS::CREATED);

        preparedS->step();
        preparedS->dispose();
    } catch (const std::exception& e) {
        printf(e.what());
    }
}

void DatabaseController::selectApp(
    int64_t userId,
    std::string app) {
    try {
        auto preparedS = MainDatabase::getDB().executeFast("UPDATE tasks SET app = ? WHERE userId = ? AND status = ?");

        preparedS->bindString(1, app);
        preparedS->bindInt64(2, userId);
        preparedS->bindInt32(3, TASK_STATUS::CREATED);

        preparedS->step();
        preparedS->dispose();
    } catch (const std::exception& e) {
        printf(e.what());
    }
}

void DatabaseController::selectBuildType(
    int64_t userId,
    std::string buildType) {
    try {
        auto preparedS = MainDatabase::getDB().executeFast("UPDATE tasks SET buildType = ? WHERE userId = ? AND status = ?");

        preparedS->bindString(1, buildType);
        preparedS->bindInt64(2, userId);
        preparedS->bindInt32(3, TASK_STATUS::CREATED);

        preparedS->step();
        preparedS->dispose();
    } catch (const std::exception& e) {
        printf(e.what());
    }
}

void DatabaseController::setTaskTitle(
    int64_t userId,
    std::string title) {
    try {
        auto preparedS = MainDatabase::getDB().executeFast("UPDATE tasks SET title = ? WHERE userId = ? AND status = ?");

        preparedS->bindString(1, title);
        preparedS->bindInt64(2, userId);
        preparedS->bindInt32(3, TASK_STATUS::CREATED);

        preparedS->step();
        preparedS->dispose();
    } catch (const std::exception& e) {
        printf(e.what());
    }
}

void DatabaseController::setTaskStatus(
    int32_t id,
    int32_t status) {
    try {
        auto preparedS = MainDatabase::getDB().executeFast("UPDATE tasks SET status = ? WHERE id = ?");

        preparedS->bindInt32(1, status);
        preparedS->bindInt32(2, id);

        preparedS->step();
        preparedS->dispose();

        if (status == TASK_STATUS::CONFIRMED) {
            for (const auto& entry : mListeners) {
                entry.second(Events::TASK_CONFIRMED);
            }
        }

    } catch (const std::exception& e) {
        printf(e.what());
    }
}

void DatabaseController::setErrorCode(
    int32_t id,
    int32_t errorCode) {
    try {
        auto preparedS = MainDatabase::getDB().executeFast("UPDATE tasks SET errorCode = ? WHERE id = ?");

        preparedS->bindInt32(1, errorCode);
        preparedS->bindInt32(2, id);

        preparedS->step();
        preparedS->dispose();
    } catch (const std::exception& e) {
        printf(e.what());
    }
}

void DatabaseController::setTaskMessageId(
    int32_t taskId,
    int64_t chatId,
    int64_t messageId) {
    try {
        auto preparedS = MainDatabase::getDB().executeFast("UPDATE tasks SET chatId = ?, messageId = ? WHERE id = ?");

        preparedS->bindInt64(1, chatId);
        preparedS->bindInt64(2, messageId);
        preparedS->bindInt32(3, taskId);

        preparedS->step();
        preparedS->dispose();
    } catch (const std::exception& e) {
        printf(e.what());
    }
}

void DatabaseController::deleteTask(int32_t id) {
    try {
        auto preparedS = MainDatabase::getDB().executeFast("DELETE FROM tasks WHERE id = ?");

        preparedS->bindInt32(1, id);

        preparedS->step();
        preparedS->dispose();
    } catch (const std::exception& e) {
        printf(e.what());
    }
}

DatabaseController::~DatabaseController() {
}