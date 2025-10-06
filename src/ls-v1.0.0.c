#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

// Function to print permissions like rwxr-xr--
void print_permissions(mode_t mode) {
    char perms[11];
    perms[0] = (S_ISDIR(mode)) ? 'd' : '-';
    perms[1] = (mode & S_IRUSR) ? 'r' : '-';
    perms[2] = (mode & S_IWUSR) ? 'w' : '-';
    perms[3] = (mode & S_IXUSR) ? 'x' : '-';
    perms[4] = (mode & S_IRGRP) ? 'r' : '-';
    perms[5] = (mode & S_IWGRP) ? 'w' : '-';
    perms[6] = (mode & S_IXGRP) ? 'x' : '-';
    perms[7] = (mode & S_IROTH) ? 'r' : '-';
    perms[8] = (mode & S_IWOTH) ? 'w' : '-';
    perms[9] = (mode & S_IXOTH) ? 'x' : '-';
    perms[10] = '\0';
    printf("%s ", perms);
}

int main(int argc, char *argv[]) {
    int long_format = 0;

    // Check if user entered -l
    if (argc > 1 && strcmp(argv[1], "-l") == 0)
        long_format = 1;

    DIR *dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        // Skip hidden files (optional)
        if (entry->d_name[0] == '.')
            continue;

        if (long_format) {
            struct stat fileStat;
            if (stat(entry->d_name, &fileStat) == -1)
                continue;

            // Permissions
            print_permissions(fileStat.st_mode);

            // Links, Owner, Group, Size, Date, Name
            printf("%2ld ", fileStat.st_nlink);
            printf("%-8s ", getpwuid(fileStat.st_uid)->pw_name);
            printf("%-8s ", getgrgid(fileStat.st_gid)->gr_name);
            printf("%8ld ", fileStat.st_size);

            char timebuf[64];
            strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&fileStat.st_mtime));
            printf("%s ", timebuf);

            printf("%s\n", entry->d_name);
        } else {
            printf("%s  ", entry->d_name);
        }
    }

    printf("\n");
    closedir(dir);
    return 0;
}

