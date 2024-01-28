#ifndef DATABASECONTROLLER_HPP
#define DATABASECONTROLLER_HPP

#include "Callback.hpp"
#include "Data.hpp"
#include "Database.hpp"
#include "FragmentStateController.hpp"
#include "MainDatabase.hpp"

class DatabaseController {
   private:
    std::vector<std::pair<int, Callback>> mListeners;

   public:
    DatabaseController();

    void createTables();

    void addListener(int id, const Callback& callback);
    void removeListener(int id);


    // user
    void resetUser(int64_t id);
    void insertUser(
        int64_t id,
        std::string firstName,
        std::string lastName,
        std::string phoneNumber,
        std::string userName);
    void updateFragmentState(
        int64_t id,
        int fragmentId);

    // task
    int32_t getCurrentTaskId(int64_t userId);
    int32_t getTaskId(int64_t chatId, int64_t messageId);
    std::unique_ptr<Task> getTask(int32_t taskId);
    std::unique_ptr<Task> getConfirmedTask();

    void selectProject(
        int64_t userId,
        std::string proejctName);
    void selectBranch(
        int64_t userId,
        std::string branchName);
    void selectBuildType(
        int64_t userId,
        std::string buildType);
    void selectApp(
        int64_t userId,
        std::string app);
    void setTaskStatus(
        int32_t id,
        int32_t status);
    void setErrorCode(
        int32_t id,
        int32_t errorCode);
    void setTaskMessageId(
        int32_t taskId,
        int64_t chatId,
        int64_t messageId);
    void deleteTask(
        int32_t taskId
    );



    ~DatabaseController();
};

#endif