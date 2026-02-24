#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "functionality.h"
#include "definitions.h"

// Last ID entry
int last_ID;

// Prototype
int file_exists (const char *file_name);
int count_rows (const char *file_name);
int csv_parser (study_log *logs_arr, const char *file_name);

int main () {

    char *file_name = "userdata/study.csv";

    // Create a new csv file if it doesn't exist.
    if (file_exists (file_name) == 0) {
        FILE *new_file = fopen (file_name, "w");
        if (new_file == NULL) {
            printf ("Error: The study.csv file could not be opened.\n");

            return 1;
        }
        fclose (new_file);
    }

    // Get the number of rows without the header
    int rows = count_rows (file_name) - 1;
    if (rows == -1) {
        return 1;
    }

    // Create a array of dynamic size
    int free_space = FREE_SPACE;

    study_log *logs_arr = malloc ((rows + free_space) * sizeof (study_log));
    if (logs_arr == NULL) {
        return 1;
    } // TODO:Checar size e usar realloc dentro da função Add_new

    // Load data into logs_arr_arr
    csv_parser (logs_arr, file_name);

    // Number of elements in the array
    int arr_size = (rows + free_space);

    add_new (logs_arr, &arr_size, &free_space);

    // Tests
    // printf ("ID: %d\n", logs->ID);
    // printf ("Subject: %s\n", logs->subject);
    // printf ("Topic: %s\n", logs->topic);
    // printf ("Start Date: %s\n", logs->start_date);
    // printf ("End Date: %s\n", logs->end_date);

    // if (logs->status == 1) {
    //     printf ("Status: FINISHED\n");
    // }
    // if (logs->status == 0) {
    //     printf ("Status: IN PROGRESS\n");
    // }

    // Get the last ID entry
    // TODO: Usar search function para encontrar ID com subject ""
    // TODO: Ao Salvar no csv lembrar de adicionar o last_ID numa linha com as outras colunas vazias

    // Exibir Menu
    //
    // 1. Add new
    // Number of elements of array

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

// Number of rows in the file
int count_rows (const char *file_name) {
    FILE *file = fopen (file_name, "r");
    if (file == NULL) {
        printf ("Error: File Not Found!\n");
        return -1;
    }

    int rows = 0;
    char ch;

    // Reads character by character until the end of the file
    while ((ch = fgetc (file)) != EOF) {
        if (ch == '\n') {
            rows++;
        }
    }

    fclose (file);
    return rows;
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
                strcpy (logs_arr->ID, value);
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
    return 0;
}
