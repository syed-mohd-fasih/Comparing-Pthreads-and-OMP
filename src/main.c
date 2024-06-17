#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>


// Checks if a specified directory exists or not
int directory_exists(const char *path) {
    struct stat statbuf;

    if (stat(path, &statbuf) != 0) {
        return 0;
    }

    return S_ISDIR(statbuf.st_mode);
}

// Creates a Directory
int create_directory(const char *dir_name) {
    if(directory_exists(dir_name)) {
        printf("\nDirectory %s already exists\n", dir_name);
        return 0;
    }
    else {
        char command[] = "mkdir -p ";
        strcat(command, dir_name);
        system(command);
        return 1;
    }
}

// Runs the specified executable within the given directory and saves given string/output to file
void run_and_save_output_to_file(const char *command, const char *output_file)
{
    FILE *fp;
    FILE *outfile;
    char buffer[1024] = {'\0'};

    fp = popen(command, "r");
    if (fp == NULL)
    {
        perror("popen failed");
        exit(EXIT_FAILURE);
    }

    outfile = fopen(output_file, "w");
    if (outfile == NULL)
    {
        perror("fopen failed");
        pclose(fp);
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        fputs(buffer, outfile);
    }

    fclose(outfile);
    pclose(fp);
}

void prepare_analysis() {
    // make analysis_report.txt in output/ dir
    // Get finishing time from sorting algos output,
    // calculate difference, average time, avg diff
    // Make summary. Automate it
}

// Runs all executables within a given directory
void execute_all_in_directory(const char *dir_path, const char *output_dir)
{
    DIR *dir;
    struct dirent *entry;
    char command[100] = {'\0'};
    char output_file[1024] = {'\0'};

    dir = opendir(dir_path);
    if (dir == NULL)
    {
        perror("opendir failed");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL)
    {
        // Skip "." and ".." entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        // Construct the command and output file paths
        snprintf(command, sizeof(command), "%s/%s", dir_path, entry->d_name);
        snprintf(output_file, sizeof(output_file), "%s_output.txt", entry->d_name);

        run_and_save_output_to_file(command, output_file);
    }

    closedir(dir);
}

void init_flags()
{
    flags.execute_omp = FALSE;
    flags.execute_pthreads = FALSE;
    flags.execute_omp_and_pthreads = FALSE;
    flags.output_generated = FALSE;
    flags.program_exit = FALSE;
    flags.gui = FALSE;
}

void _key() {
    printf("\t====== Press any key to continue ======\n");
    getchar();
    system("CLS");
}

int menu()
{
    system("CLS");

    printf("=== Comparing Pthreads and OpenMP ===\n");
    printf("\t1. Execute OMP implementations\n");
    printf("\t2. Execute Pthreads implementations\n");
    printf("\t3. Execute Both implementations\n");
    printf("\t4. Prepare Analysis Report\n");
    printf("\t5. Settings\n");
    printf("\t6. About Project\n");
    printf("\t7. Stats\n");
    printf("\t8. Enable GUI (Coming Soon)\n");
    printf("\t9. Exit Program\n");

    printf("\n\tEnter choice: ");
    int choice = 0;
    scanf("%d", &choice);

    if(choice > 0 && choice < 10) 
        return choice;
    else {
        printf("\nInvalid Input\n");
        _key();
        return -1;
    }
}

enum boolean
{
    FALSE,
    TRUE
};

struct Flags
{
    enum boolean execute_omp,
        execute_pthreads,
        execute_omp_and_pthreads,
        output_generated,
        program_exit,
        gui;
} flags;

int main()
{
    int choice = 0;
    while (!flags.program_exit)
    {
        choice = menu();

        switch(choice) {
            case 1:
                if(!flags.execute_omp)
                    execute_all_in_directory("./omp", "../output/omp");
                else
                    if(directory_exists("../output/omp") && flags.execute_omp) {
                        printf("Output already exists,\nif you encounter errors or issues with this\n"
                            "Please exit the program and run `make clean` and rerun the project.\n");
                        _key();
                    }
                    else
                        printf("Something went wrong");
                break;
            case 2:
                if(!flags.execute_pthreads)
                    execute_all_in_directory("./pthreads", "../output/pthreads");
                else
                    if(directory_exists("../output/pthreads") && flags.execute_pthreads) {
                        printf("Output already exists,\nif you encounter errors or issues with this\n"
                        "Please exit the program and run `make clean` and rerun the project.\n");
                        _key();
                    }
                    else
                        printf("Something went wrong");
                break;
            case 3:
                if(!flags.execute_omp)
                    execute_all_in_directory("./omp", "../output/omp");
                if(!flags.execute_pthreads)
                    execute_all_in_directory("./pthreads", "../output/pthreads");
                if((directory_exists("../output/omp") && flags.execute_omp) && (directory_exists("../output/pthreads") && flags.execute_pthreads)) {
                    printf("Output already exists,\nif you encounter errors or issues with this\n"
                    "Please exit the program and run `make clean` and rerun the project.\n");
                    _key();
                }
                else
                    printf("Something went wrong");
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            default:
        }

    }

    return 0;
}