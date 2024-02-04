#ifndef GIT_MANAGER_HPP
#define GIT_MANAGER_HPP

#include <git2.h>

#include <algorithm>
#include <cstring>
#include <filesystem>
#include <gitty.hpp>
#include <vector>

#include "iostream"
#include "utils.hpp"

struct CredentialsPayload {
    const char* username;
    const char* password;
};

class GitManager {
   private:
    static const CredentialsPayload& getCredentials(
        const char* username,
        const char* password) {
        static CredentialsPayload credentialsPayload = {username, password};
        return credentialsPayload;
    }

    static int credentialsCallback(
        git_cred** out,
        const char* url,
        const char* username_from_url,
        unsigned int allowed_types,
        void* payload) {
        const CredentialsPayload& credentialsPayload = getCredentials(nullptr, nullptr);
        git_cred_userpass_plaintext_new(out, credentialsPayload.username, credentialsPayload.password);
        return 0;
    }

   public:
    GitManager();

    static void init(
        const char* username,
        const char* token,
        const char* repoUrl,
        const char* localPath);

    void getBranches(const std::string& localPath, std::vector<std::string>& branches);

    void fetch(const std::string& localPath);

    void checkout(const std::string& localPath, const std::string& branch);

    ~GitManager();
};

#endif