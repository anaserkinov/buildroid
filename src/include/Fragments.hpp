#ifndef FRAGMENTS
#define FRAGMENTS

#include <iostream>
#include <vector>

#include "DatabaseController.hpp"
#include "Fragment.hpp"

class Fragments {
   public:
    static const int LOGIN = 2;
    static const int MAIN = 3;
    static const int TAXI = 4;
    static const int APP = 5;
    static const int BUILD_TYPE = 6;
    static const int NOTE = 7;
    static const int CONFIRM = 8;
};

class BaseFragment : public Fragment {
   protected:
    DatabaseController* dbController = nullptr;

   public:
    BaseFragment(int id);
    void onCreate(int16_t type, const std::shared_ptr<void>& data) override;
    void setDBController(DatabaseController* dbController);
    ~BaseFragment();
};

class LoginFragment : public BaseFragment {
    std::vector<std::string> admins;

   public:
    LoginFragment();
    void onCommand(const Message::Ptr& message) override;
    void onNonCommandMessage(const Message::Ptr& message) override;
};

class MainFragment : public BaseFragment {
   public:
    MainFragment();
    void onCreate(int16_t type, const std::shared_ptr<void>& data) override;
    void onNonCommandMessage(const Message::Ptr& message) override;
};

class TaxiFragment : public BaseFragment {
   public:
    TaxiFragment();
    void onCreate(int16_t type, const std::shared_ptr<void>& data) override;
    void onNonCommandMessage(const Message::Ptr& message) override;
};

class AppFragment : public BaseFragment {
   public:
    AppFragment();
    void onCreate(int16_t type, const std::shared_ptr<void>& data) override;
    void onNonCommandMessage(const Message::Ptr& message) override;
};

class BuildTypeFragment : public BaseFragment {
   public:
    BuildTypeFragment();
    void onCreate(int16_t type, const std::shared_ptr<void>& data) override;
    void onNonCommandMessage(const Message::Ptr& message) override;
};

class NoteFragment : public BaseFragment {
   public:
    NoteFragment();
    void onCreate(int16_t type, const std::shared_ptr<void>& data) override;
    void onNonCommandMessage(const Message::Ptr& message) override;
};

class ConfirmFragment : public BaseFragment {
   public:
    ConfirmFragment();
    void onCreate(int16_t type, const std::shared_ptr<void>& data) override;
    void onCallbackQuery(const CallbackQuery::Ptr& callbackQuery) override;
};

#endif