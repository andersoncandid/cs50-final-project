#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define TITLE_LENGTH 128
#define DATE_LENGTH 20
#define NOTES_LENGTH 4096

int file_exists (const char *file_name);
long int find_size (const char *file_name);

typedef enum { FINISHED = 0, IN_PROGRESS = 1, REMOVED = 2 } study_status;

// Study record structure
typedef struct {
    int ID;
    char subject[TITLE_LENGTH];
    char topic[TITLE_LENGTH];
    char notes[NOTES_LENGTH];
    char start_date[DATE_LENGTH];
    char end_date[DATE_LENGTH];
    study_status status;
} study_log;

int main () {

    char *file_path = "../userdata/study.csv";

    // Create a new csv file even if it doesn't exist.
    if (file_exists (file_path) == 0) {
        FILE *new_file = fopen (file_path, "w");
        if (new_file == NULL) {
            printf ("Error: The study.csv file could not be opened.\n");
            fclose (new_file);
            return 1;
        }
        fclose (new_file);
    }

    // Find the size of the CSV file.
    int file_size = find_size (file_path);
    if (file_size == -1) {
        return 1;
    }

    // Create a array of dynamic size
    int free_space = 100;

    study_log *logs = malloc ((file_size + free_space) * sizeof (study_log));
    if (logs == NULL) {
        return 1;
    }

    // Carregar log na logs array

    // Exibir Menu
    // 1. Add new
    // 2. Edit log
    //  - modificar
    //  - remover
    //  3. Find by Struct Key
    //  4. Show Unfinished
    //  5. Show by month
    //  6. Save Changes
    //  8. Exit
    //  Nota:  No Readme instruçao de onde e como gerenciar o arquivo salvo
    //  log.csv

    // Salvar no csv com uma opçao no menu e ao fechar perguntar se deseja salvar
    // (igual vim) criar funçao salve_csv()
}

// Check if file exist
int file_exists (const char *file_name) {
    struct stat buffer;

    if (stat (file_name, &buffer) == 0) {
        return 1; // File exists

    } else {
        return 0;
    }
}

// Find the size of file
// source:https://www.geeksforgeeks.org/c/c-program-find-size-file/
long int find_size (const char *file_name) {

    FILE *file = fopen (file_name, "r");
    if (file == NULL) {
        printf ("Error: File Not Found!\n");
        fclose (file);
        return -1;
    }

    fseek (file, 0L, SEEK_END);

    // calculating the size of the file
    long int size = ftell (file);

    fclose (file);

    return size;
}

// Parsing the CSV log file
int csv_parser (study_log *logs_arr, const char *file_name, size_t size_study_log) {

    FILE *file = fopen (file_name, "r");
    if (file == NULL) {
        printf ("Error: The study.csv file could not be opened.\n");
        return -1;
    }

    char buffer[size_study_log + 10];

    int row = 0;
    int column = 0;

    // source: https://www.geeksforgeeks.org/c/relational-database-from-csv-files-in-c/
    while (fgets (buffer, sizeof (buffer), file) != NULL) {
        column = 0;
        row++;

        // Skip first row
        if (row == 1)
            continue;

        // Splitting the data
        char *value = strtok (buffer, ", ");

        while (value) {
            // Column 1
            if (column == 0) {
                printf ("Name :");
            }

            // Column 2
            if (column == 1) {
                printf ("\tAccount No. :");
            }

            // Column 3
            if (column == 2) {
                printf ("\tAmount :");
            }

            printf ("%s", value);
            value = strtok (NULL, ", ");
            column++;
        }
    }
}
