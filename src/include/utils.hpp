#ifndef UTILS_HPP
#define UTILS_HPP

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>

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
};

#endif