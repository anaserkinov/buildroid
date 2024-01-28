#ifndef DATA_HPP
#define DATA_HPP

#include <string>

struct Task {
    int64_t id;
    int64_t userId;
    std::string project;
    std::string branch;
    std::string app;
    std::string buildType;
    int32_t status;
    int32_t errorCode;
    int64_t charId;
    int64_t messageId;
};

#endif