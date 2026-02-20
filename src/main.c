#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define ENTRY_LENGTH 128
#define DATE_LENGTH 20
#define FREE_SPACE 100

typedef enum { IN_PROGRESS, FINISHED, REMOVED } study_status;

// Study record structure
typedef struct {
    int ID;
    char subject[ENTRY_LENGTH];
    char topic[ENTRY_LENGTH];
    char start_date[DATE_LENGTH];
    char end_date[DATE_LENGTH];
    study_status status;
} study_log;

// Last ID entry
int last_ID;

// Functions prototypes
int file_exists (const char *file_name);
long int find_size (const char *file_name);
int csv_parser (study_log *logs_arr, const char *file_name);

int main () {

    char *file_name = "../userdata/study.csv";

    // Create a new csv file even if it doesn't exist.
    if (file_exists (file_name) == 0) {
        FILE *new_file = fopen (file_name, "w");
        if (new_file == NULL) {
            printf ("Error: The study.csv file could not be opened.\n");
            fclose (new_file);
            return 1;
        }
        fclose (new_file);
    }

    // Get the size of the CSV file.
    int file_size = find_size (file_name);
    if (file_size == -1) {
        return 1;
    }

    // Create a array of dynamic size
    int free_space = FREE_SPACE;

    study_log *logs = malloc ((file_size + free_space) * sizeof (study_log));
    if (logs == NULL) {
        return 1;
    } // TODO:Checar size e usar realloc dentro da função Add_new

    // Load data into logs_arr
    csv_parser (logs, file_name);

    // Tests
    printf ("ID: %d\n", logs->ID);
    printf ("Subject: %s\n", logs->subject);
    printf ("Topic: %s\n", logs->topic);
    printf ("Start Date: %s\n", logs->start_date);
    printf ("End Date: %s\n", logs->end_date);
    if (logs->status == 1) {
        printf ("Status: FINISHED\n");
    }
    if (logs->status == 0) {
        printf ("Status: IN PROGRESS\n");
    }

    // Get the last ID entry
    // TODO: Usar search function para encontrar ID com subject ""
    // TODO: Ao Salvar no csv lembrar de adicionar o last_ID numa linha com as outras colunas vazias

    // Exibir Menu
    // 1. Add new
    // 2. Edit log
    //  - modificar
    //  - remover >> Usar status 2 na array
    //  3. Find by Struct Key
    //  4. Show Unfinished
    //  5. Show by month
    //  6. Save Changes >> nao adicionar ao arquivo status == 2 [REMOVED]
    //  8. Exit >> Perguntar se deseja salvar
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
int csv_parser (study_log *logs_arr, const char *file_name) {

    FILE *file = fopen (file_name, "r");
    if (file == NULL) {
        printf ("Error: The study.csv file could not be opened.\n");
        return -1;
    }

    char buffer[1024];

    int row = 0;
    int column = 0;

    // Parsing line by line
    while (fgets (buffer, sizeof (buffer), file)) {
        column = 0;
        row++;

        // Skip first row
        if (row == 1)
            continue;

        // Splitting the data
        char *value = strtok (buffer, ",");

        while (value) {
            if (column == 0) {
                logs_arr->ID = atoi (value);
            }

            if (column == 1) {
                strcpy (logs_arr->subject, value);
            }

            if (column == 2) {
                strcpy (logs_arr->topic, value);
            }

            if (column == 3) {
                strcpy (logs_arr->start_date, value);
            }
            if (column == 4) {
                strcpy (logs_arr->end_date, value);
            }

            if (column == 5) {
                if (*value == 'I') {
                    logs_arr->status = IN_PROGRESS;
                }
                if (*value == 'F') {
                    logs_arr->status = FINISHED;
                }
            }

            value = strtok (NULL, ",");
            column++;
        }
    }
}
