#ifndef DATABASECONTROLLER_HPP
#define DATABASECONTROLLER_HPP

#include "Data.hpp"
#include "Database.hpp"
#include "MainDatabase.hpp"
#include "FragmentStateController.hpp"

class DatabaseController {
    void getApp(App app, CursorPtr& cursor);

public:
    DatabaseController();

    void createTables();

    std::shared_ptr<FragmentState> getFragmentState(std::string userId);

    void insertApp(App app);
    void updateApp(App app);
    App* getApps(int64_t userId);
    App getApp(int64_t id);
    void deleteApp(int64_t id);

    // void insertAppUpdate(AppUpdate appUpdate);
    // void updateAppUpdate(AppUpdate appUpdate);
    // App getAppUpdate(int64_t id);
    // void deleteAppUpdate(int64_t id);

    ~DatabaseController();
};

#endif