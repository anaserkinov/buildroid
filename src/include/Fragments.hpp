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
    static const int BUILD_TYPE = 5;
    static const int APP = 6;
};

class BaseFragment : public Fragment {
   protected:
    DatabaseController* dbController = nullptr;

   public:
    BaseFragment(int id);
    void onCreate(const Message::Ptr& lastMessage) override;
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
    void onCreate(const Message::Ptr& lastMessage) override;
    void onNonCommandMessage(const Message::Ptr& message) override;
};

class TaxiFragment : public BaseFragment {
   public:
    TaxiFragment();
    void onCreate(const Message::Ptr& lastMessage) override;
    void onNonCommandMessage(const Message::Ptr& message) override;
};

class BuildTypeFragment : public BaseFragment {
   public:
    BuildTypeFragment();
    void onCreate(const Message::Ptr& lastMessage) override;
    void onNonCommandMessage(const Message::Ptr& message) override;
};

class AppFragment : public BaseFragment {
   public:
    AppFragment();
    void onCreate(const Message::Ptr& lastMessage) override;
    void onNonCommandMessage(const Message::Ptr& message) override;
};

#endif