#ifndef DATABASECONTROLLER_HPP
#define DATABASECONTROLLER_HPP

#include "Data.hpp"
#include "Database.hpp"
#include "FragmentStateController.hpp"
#include "MainDatabase.hpp"

class DatabaseController {
    void getApp(App app, CursorPtr& cursor);

public:
    DatabaseController();

    void createTables();

    void insertUser(
            int64_t id,
            std::string firstName,
            std::string lastName,
            std::string phoneNumber,
            std::string userName);
    void updateFragmentState(
            int64_t id,
            int fragmentId);

    App* getApps(int64_t userId);

    ~DatabaseController();
};

#endif