#ifndef GIT_MANAGER_HPP
#define GIT_MANAGER_HPP

#include <git2.h>

#include <cstring>
#include <gitty.hpp>
#include <vector>
#include "iostream"
#include <filesystem>
#include "utils.hpp"
#include <algorithm>

struct CredentialsPayload {
    const char* username;
    const char* password;
};

class GitManager {
   private:
    static int credentialsCallback(
        git_cred** out,
        const char* url,
        const char* username_from_url,
        unsigned int allowed_types,
        void* payload) {
        CredentialsPayload* credentialsPayload = static_cast<CredentialsPayload*>(payload);
        git_cred_userpass_plaintext_new(out, credentialsPayload->username, credentialsPayload->password);
        return 0;
    }

   public:
    GitManager();

    static void init(
        const char* username,
        const char* token,
        const char* repoUrl,
        const char* localPath);

    void getBranches(const char* localPath, std::vector<std::string>& branches);

    ~GitManager();
};

#endif