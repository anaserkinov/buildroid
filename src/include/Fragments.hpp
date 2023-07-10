#ifndef FRAGMENTS
#define FRAGMENTS

#include "DatabaseController.hpp"
#include "Fragment.hpp"

class Fragments {
public:
    static const int LOGIN = 2;
};

class BaseFragment : public Fragment {
    DatabaseController* dbController = nullptr;

public:
    BaseFragment(int id);
    void setDBController(DatabaseController* dbController);
    ~BaseFragment();
};

class LoginFragment : public BaseFragment {
public:
    LoginFragment();
    // void onCreate(const Bot& bot, const Api api) override;
    void onNonCommandMessage(const Message::Ptr& message) override;
};

#endif