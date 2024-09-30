#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

void printPermissions(mode_t mode) {
    printf( (S_ISDIR(mode)) ? "d" : "-");
    printf( (mode & S_IRUSR) ? "r" : "-");
    printf( (mode & S_IWUSR) ? "w" : "-");
    printf( (mode & S_IXUSR) ? "x" : "-");
    printf( (mode & S_IRGRP) ? "r" : "-");
    printf( (mode & S_IWGRP) ? "w" : "-");
    printf( (mode & S_IXGRP) ? "x" : "-");
    printf( (mode & S_IROTH) ? "r" : "-");
    printf( (mode & S_IWOTH) ? "w" : "-");
    printf( (mode & S_IXOTH) ? "x" : "-");
}

void listFiles(const char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        char fullPath[1024];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", path, entry->d_name);

        struct stat fileStat;
        if (stat(fullPath, &fileStat) < 0) {
            perror("stat");
            continue;
        }

        printPermissions(fileStat.st_mode);
        printf(" %ld", (long)fileStat.st_nlink);

        struct passwd *pw = getpwuid(fileStat.st_uid);
        struct group  *gr = getgrgid(fileStat.st_gid);
        printf(" %s %s", pw->pw_name, gr->gr_name);

        printf(" %5ld", (long)fileStat.st_size);

        char timeBuf[80];
        struct tm *timeinfo = localtime(&fileStat.st_mtime);
        strftime(timeBuf, sizeof(timeBuf), "%b %d %H:%M", timeinfo);
        printf(" %s", timeBuf);

        printf(" %s\n", entry->d_name);
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    const char *path = (argc > 1) ? argv[1] : ".";
    listFiles(path);
    return 0;
}
