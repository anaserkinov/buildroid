#ifndef BUILDRROID_UTILS_HPP
#define BUILDRROID_UTILS_HPP

#include <Data.hpp>
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Events {
   public:
    static const int TASK_CONFIRMED;
};

class TASK_TYPE {
   public:
    static const int BUILD;
    static const int SEND;
};

class TASK_STATUS {
   public:
    static const int CREATED;
    static const int NEW;
    static const int CONFIRMED;
    static const int IN_PROGRESS;
    static const int COMPLETED;
    static const int FAILED;
    static const int CANCELED;
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

    static std::string execute(const std::string& command) {
        FILE* pipe = popen(command.c_str(), "r");
        if (!pipe) {
            std::cerr << "Error opening pipe." << std::endl;
            return "error";
        }

        char buffer[128];
        std::string result = "";
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            result += buffer;
        }
        int status = pclose(pipe);

        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            return result;
        } else {
            std::cerr << "Error executing command." << std::endl;
            if (!result.empty()) {
                std::cerr << "Error message: " << result << std::endl;
            }
            return "error";
        }
    }

    static std::string getVersionCode(const std::string filePath){
        return Utils::execute("aapt dump badging \"" + filePath + "\" | awk -v FS=\"'\" '/versionName/{print $4}'");
    }

    static std::string getVersionName(const std::string filePath){
        return Utils::execute("aapt dump badging \"" + filePath + "\" | awk -v FS=\"'\" '/versionName/{print $6}'");
    }

    static void clearStringFromSticker(std::string& s) {
        s.erase(std::remove_if(s.begin(), s.end(), isNotAlphanumeric), s.end());

        while (!s.empty() && s.back() == ' ') {
            s.pop_back();
        }
    }

    static bool isFolderExists(const std::string& folder) {
        return std::filesystem::exists(folder) && std::filesystem::is_directory(folder);
    }

    static const std::vector<std::string> getTaxiApps() {
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
            "yataxi"};
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
            text += "</b>\nTitle: <b>";
            text += task->title;
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
            text += "</b>\nTitle: <b>";
            text += task->title;
            text += "</b>";
            return text;
        } else if (task->status == TASK_STATUS::IN_PROGRESS) {
            std::string text = "<strong>In progress ...</strong>\n\nProject: <b>";
            text += task->project;
            text += "</b>\nBranch: <b>";
            text += task->branch;
            text += "</b>\nApp: <b>";
            text += task->app;
            text += "</b>\nType: <b>";
            text += task->buildType;
            text += "</b>\nTitle: <b>";
            text += task->title;
            text += "</b>";
            return text;
        } else {
            std::string text = "<strong>Completed ...</strong>\n\nProject: <b>";
            text += task->project;
            text += "</b>\nBranch: <b>";
            text += task->branch;
            text += "</b>\nApp: <b>";
            text += task->app;
            text += "</b>\nType: <b>";
            text += task->buildType;
            text += "</b>\nTitle: <b>";
            text += task->title;
            text += "</b>";
            return text;
        }
    }

    static std::string toLowercase(const std::string& str) {
        std::string result;
        for (char c : str) {
            result += std::tolower(c);
        }
        return result;
    }
};

#endif