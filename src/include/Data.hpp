#ifndef DATA_HPP
#define DATA_HPP

#include <string>

struct App {
    int64_t id;
    int64_t userId;
    std::string name;
    std::string versionName;
    int versionCode;
};

struct AppUpdate {
    int64_t id;
    int64_t appId;
    std::string versionName;
    int versionCode;
};

#endif