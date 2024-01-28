#ifndef UTILS_HPP
#define UTILS_HPP

#include <Data.hpp>
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>

class Events {
   public:
    static const int TASK_CONFIRMED = 2;
};

class TASK_STATUS {
   public:
    static const int CREATED = 1;
    static const int NEW = 2;
    static const int CONFIRMED = 3;
    static const int IN_PROGRESS = 4;
    static const int COMPLETED = 5;
    static const int FAILED = 6;
    static const int CANCELED = 7;
};

class Utils {
   private:
    static bool isNotAlphanumeric(char c) {
        return !(std::isalnum(static_cast<unsigned char>(c)) || c == ' ');
    }

   public:
    static const std::string workDir;
    static const std::string taxiPath;
    static const std::string bitoPath;

    static void clearStringFromSticker(std::string& s) {
        s.erase(std::remove_if(s.begin(), s.end(), isNotAlphanumeric), s.end());

        while (!s.empty() && s.back() == ' ') {
            s.pop_back();
        }
    }

    static bool isFolderExists(const std::string& folder) {
        return std::filesystem::exists(folder) && std::filesystem::is_directory(folder);
    }

    static const std::vector<std::string> getTaxiApps(){
        std::vector<std::string> apps = {
            "alotaxi",
            "brandtaxi",
            "cardintaxi",
            "demotaxi",
            "expresstaxi",
            "hamkortaxi",
            "lifetaxi",
            "milliytaxi",
            "onlinetaxi",
            "salamtaxi",
            "startaxi",
            "unicaltaxi",
            "yataxi"
        };
        return apps;
    }

    static std::vector<std::string> splitString(const std::string& str, const char separator) {
        std::vector<std::string> tokens;
        std::istringstream ss(str);
        std::string token;
        while (std::getline(ss, token, separator)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    static std::string getTaskInfoText(const std::unique_ptr<Task>& task) {
        if (task->status == TASK_STATUS::NEW) {
            std::string text = "<strong>Confirmation:</strong>\n\nProject: <b>";
            text += task->project;
            text += "</b>\nBranch: <b>";
            text += task->branch;
            text += "</b>\nApp: <b>";
            text += task->app;
            text += "</b>\nType: <b>";
            text += task->buildType;
            text += "</b>";
            return text;
        } else if (task->status == TASK_STATUS::CONFIRMED) {
            std::string text = "<strong>Wait ...</strong>\n\nProject: <b>";
            text += task->project;
            text += "</b>\nBranch: <b>";
            text += task->branch;
            text += "</b>\nApp: <b>";
            text += task->app;
            text += "</b>\nType: <b>";
            text += task->buildType;
            text += "</b>";
            return text;
        } else {
            std::string text = "<strong>In progress ...</strong>\n\nProject: <b>";
            text += task->project;
            text += "</b>\nBranch: <b>";
            text += task->branch;
            text += "</b>\nApp: <b>";
            text += task->app;
            text += "</b>\nType: <b>";
            text += task->buildType;
            text += "</b>";
            return text;
        }
    }
};

#endif