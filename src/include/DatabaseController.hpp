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
    void selectProject(
        int64_t id,
        std::string proejctName);
    void selectBranch(
        int64_t id,
        std::string branchName);
    void selectBuildType(
        int64_t id,
        std::string buildType);
    void selectApp(
        int64_t id,
        std::string app);

    App* getApps(int64_t userId);

    ~DatabaseController();
};

#endif