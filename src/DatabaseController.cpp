#include "DatabaseController.hpp"

#include "Fragments.hpp"

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
                                 "fragmentId INTEGER,"
                                 "project TEXT,"
                                 "branch TEXT,"
                                 "buildType TEXT,"
                                 "app TEXT"
                                 ")")
            ->stepThis()
            .dispose();
        MainDatabase::getDB().executeFast(
                                 "CREATE TABLE IF NOT EXISTS apps("
                                 "id INTEGER NOT NULL PRIMARY KEY,"
                                 "firstName TEXT,"
                                 "lastName TEXT,"
                                 "phoneNumber TEXT,"
                                 "userName TEXT,"
                                 "fragmentId INTEGER"
                                 ")")
            ->stepThis()
            .dispose();
    } catch (const std::exception& e) {
        printf(e.what());
        throw e;
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
            "REPLACE INTO users VALUES(?,?,?,?,?,?,?,?,?,?)");

        std::cout << "inset: " << id << "\n";
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

void DatabaseController::selectProject(
    int64_t id,
    std::string projectName) {
    try {
        auto preparedS = MainDatabase::getDB().executeFast("UPDATE users SET project = ? WHERE id = ?");

        preparedS->bindString(1, projectName);
        preparedS->bindInt64(2, id);

        preparedS->step();
        preparedS->dispose();
    } catch (const std::exception& e) {
        printf(e.what());
    }
}

void DatabaseController::selectBranch(
    int64_t id,
    std::string branchName) {
    try {
        auto preparedS = MainDatabase::getDB().executeFast("UPDATE users SET branch = ? WHERE id = ?");

        preparedS->bindString(1, branchName);
        preparedS->bindInt64(2, id);

        preparedS->step();
        preparedS->dispose();
    } catch (const std::exception& e) {
        printf(e.what());
    }
}

void DatabaseController::selectBuildType(
    int64_t id,
    std::string buildType) {
    try {
        auto preparedS = MainDatabase::getDB().executeFast("UPDATE users SET buildType = ? WHERE id = ?");

        preparedS->bindString(1, buildType);
        preparedS->bindInt64(2, id);

        preparedS->step();
        preparedS->dispose();
    } catch (const std::exception& e) {
        printf(e.what());
    }
}

void DatabaseController::selectApp(
    int64_t id,
    std::string app) {
    try {
        auto preparedS = MainDatabase::getDB().executeFast("UPDATE users SET app = ? WHERE id = ?");

        preparedS->bindString(1, app);
        preparedS->bindInt64(2, id);

        preparedS->step();
        preparedS->dispose();
    } catch (const std::exception& e) {
        printf(e.what());
    }
}

App* DatabaseController::getApps(int64_t userId) {
    CursorPtr cursor = nullptr;
    App* apps = nullptr;
    try {
        auto db = MainDatabase::getDB();

        List<Object> args = {userId};
        cursor = db.queryFinalized("SELECT COUNT(id) FROM apps WHERE userId = ?", args);

        int count = 0;
        if (cursor->next()) {
            count = cursor->intValue(0);
        }
        cursor->dispose();

        apps = new App[count];

        if (count != 0) {
            cursor = db.queryFinalized("SELECT * FROM apps WHERE userId = ?", args);

            count = 0;
            while (cursor) {
                App app;
                getApp(app, cursor);
                apps[count] = app;
                count++;
            }
        }
    } catch (const std::exception& e) {
        apps = new App[0];
    }

    if (cursor != nullptr) {
        cursor->dispose();
    }

    return apps;
}

void DatabaseController::getApp(App app, CursorPtr& cursor) {
    app.id = cursor->intValue(0);
    app.userId = cursor->intValue(1);
    app.name = cursor->stringValue(2);
    app.versionName = cursor->stringValue(3);
    app.versionCode = cursor->intValue(4);
}

DatabaseController::~DatabaseController() {
}