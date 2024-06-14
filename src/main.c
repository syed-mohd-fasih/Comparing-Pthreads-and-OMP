#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

// Runs the specified executable within the given directory and saves given string/output to file
void save_output_to_file(const char *command, const char *output_file) {
    FILE *fp;
    FILE *outfile;
    char buffer[1024];

    fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen failed");
        exit(EXIT_FAILURE);
    }

    outfile = fopen(output_file, "w");
    if (outfile == NULL) {
        perror("fopen failed");
        pclose(fp);
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        fputs(buffer, outfile);
    }

    fclose(outfile);
    pclose(fp);
}

// Runs all executables within a given directory
void execute_all_in_directory(const char *dir_path) {
    DIR *dir;
    struct dirent *entry;
    char command[100];
    char output_file[1024];

    dir = opendir(dir_path);
    if (dir == NULL) {
        perror("opendir failed");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".." entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construct the command and output file paths
        snprintf(command, sizeof(command), "%s/%s", dir_path, entry->d_name);
        snprintf(output_file, sizeof(output_file), "%s_output.txt", entry->d_name);

        save_output_to_file(command, output_file);
    }

    closedir(dir);
}

int main() {

    return 0;
}