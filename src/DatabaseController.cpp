#include "DatabaseController.hpp"

DatabaseController::DatabaseController() {
}

void DatabaseController::createTables() {
    auto db = MainDatabase::getDB();

    db.executeFast(
              "CREATE TABLE IF NOT EXISTS users("
              "id INTEGER PRIMARY KEY,"
              "firstName TEXT,"
              "lastName TEXT,"
              "userName TEXT,"
              "fragmentId INTEGER,"
              "fragmentState INTEGER"
              ")")
            ->stepThis()
            .dispose();
}


void DatabaseController::insertApp(App app) {
    PreparedStatementPtr preparedS = nullptr;
    try {
        auto db = MainDatabase::getDB();

        preparedS = db.executeFast("");

        preparedS->requery();
        preparedS->bindInt(1, app.userId);
        // preparedS->bind (2, app.name);
        preparedS->bindInt(3, app.userId);
        preparedS->bindInt(4, app.userId);

        preparedS->step();
        preparedS->dispose();
    } catch (const std::exception& e) {
    }
}

void DatabaseController::updateApp(App app) {
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

App DatabaseController::getApp(int64_t id) {
}

void DatabaseController::deleteApp(int64_t id) {
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