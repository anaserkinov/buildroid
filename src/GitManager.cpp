#include "GitManager.hpp"

void GitManager::init(
    const char* username,
    const char* token,
    const char* repoUrl,
    const char* localPath) {
    std::string repoFolder = localPath;

    getCredentials(
        username,
        token);

    if (std::filesystem::exists(repoFolder) && std::filesystem::is_directory(repoFolder)) {
        std::cout << "Repo exists." << std::endl;
    } else {
        git_repository* repo = nullptr;
        git_clone_options clone_opts = GIT_CLONE_OPTIONS_INIT;
        clone_opts.fetch_opts.callbacks.credentials = credentialsCallback;
        // clone_opts.fetch_opts.callbacks.payload = &credentialsPayload;

        int result = git_clone(&repo, repoUrl, repoFolder.c_str(), &clone_opts);
        if (result != 0) {
            const git_error* error = giterr_last();
            if (error) {
                printf("Error: %s\n", error->message);
            }
        } else {
            printf("Repository cloned successfully.\n");
        }

        git_repository_free(repo);
    }
}

GitManager::GitManager() {
}

void GitManager::getBranches(const char* localPath, std::vector<std::string>& branches) {
    git_repository* repo = nullptr;

    git_repository_open(&repo, localPath);

    git_reference_iterator* iter = nullptr;
    git_reference_iterator_new(&iter, repo);

    git_reference* ref = nullptr;
    while (git_reference_next(&ref, iter) == 0) {
        const char* full_ref_name = git_reference_name(ref);

        if (strcmp(full_ref_name, "refs/remotes/origin/HEAD") == 0) {
            // Skip refs/remotes/origin/HEAD
            git_reference_free(ref);
            continue;
        }
        if (strncmp(full_ref_name, "refs/heads/", 11) == 0) {
            // Local branch
            // const char* branch_name = full_ref_name + 11;
        } else if (strncmp(full_ref_name, "refs/remotes/origin/", 20) == 0) {
            // Remote branch
            const char* remote_branch_name = full_ref_name + 20;
            branches.emplace_back(remote_branch_name);
        }

        git_reference_free(ref);
    }

    git_reference_iterator_free(iter);
    git_repository_free(repo);
}

void GitManager::fetch(const char* localPath) {
    git_repository* repo = nullptr;

    git_repository_open(&repo, localPath);

    git_remote* remote = nullptr;
    const char* remote_name = "origin";
    int lookup_result = git_remote_lookup(&remote, repo, remote_name);
    if (lookup_result != 0) {
        const git_error* error = giterr_last();
        if (error) {
            printf("git_remote_lookup error: %s\n", error->message);
        }
    }

    git_fetch_options fetch_opts = GIT_FETCH_OPTIONS_INIT;
    fetch_opts.callbacks.credentials = credentialsCallback;

    int fetch_result = git_remote_fetch(remote, NULL, &fetch_opts, "fetch");
    if (fetch_result != 0) {
        const git_error* error = giterr_last();
        if (error) {
            printf("git_remote_fetch error: %s\n", error->message);
        }
    }
}

GitManager::~GitManager() {
}