#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "functionality.h"
#include "definitions.h"

// Prototype
int file_exists (const char *file_name);
int count_rows (const char *file_name);
int csv_parser (study_log *logs_arr, const char *file_name);

int main ()
{

    char *file_name = "userdata/study.csv";

    // Create a new csv file if it doesn't exist.
    if (file_exists (file_name) == 0)
    {
        FILE *new_file = fopen (file_name, "w");
        if (new_file == NULL) {
            printf ("Error: The study.csv file could not be opened.\n");

            return 1;
        }
        fclose (new_file);
    }

    // Number of valid elements in the array
    int rows;
    size_t arr_size;

    // Get the number of rows without the header
    rows = count_rows (file_name) - 1;
    if (rows < 0)
    {
        return 1;
    }

    arr_size = rows;

    size_t free_space = FREE_SPACE;
    size_t arr_max = (arr_size + free_space);

    // Create a array of dynamic size
    study_log *logs_arr = malloc ((arr_max) * sizeof (study_log));

    if (logs_arr == NULL)
    {
        return 1;
    }

    // Load data into logs_arr_arr
    csv_parser (logs_arr, file_name);

    // Get the last ID entry
    char last_ID[50];
    sort_arr(logs_arr, arr_size, "0");

    strcpy(last_ID, logs_arr[arr_size - 1].ID);

/* -------------------------------------------------------------------------------- */

    // User Menu main loop
        // printf("\n\n=============== WELCOME TO STUDY LOG ===============\n");
        // printf("\n\n1. Add new entry.\n");
        // printf("2. Search logs.\n");
        // printf("3. \n");
        // printf("4. List the count of book" "s in the library\n");
        // printf("5. Exit");
        //
        // // Enter the book details
        // printf("\n\nEnter one of "
        //        "the above: ");

    // 1. Add new
        // add_new(&logs_arr, &arr_size, &free_space, last_ID );

    // 2. Edit log status by ID
        char target_id[DATE_LENGTH];
        int target_index;

        printf("Enter log ID: ");
        string_input (target_id, sizeof (target_id));
        target_index = search_ID(logs_arr,arr_size, target_id);

        // Check if the ID was not found
        if (target_index == - 1)
        {
            return 1; // TODO: Valtar para o menu
        }

        // Enter edit functionality
        if (edit_log(logs_arr, arr_size, target_index) == 1)
        {
            return 1; // TODO: Valtar para o menu
        }

        printf("%s\n", logs_arr[target_index].end_date);
        printf("%s\n", logs_arr[target_index].status);

    //  3. Find by Struct Key

    //  4. Show Unfinished

    //  5. Show by month
    //  6. Save Changes >> nao adicionar ao arquivo status == 2 [REMOVED]
    //  8. Exit >> Perguntar se deseja salvar
    //  TODO: Ao salvar pular status == 2

    //  Nota:  No Readme instruçao de onde e como gerenciar o arquivo salvo
    //  log.csv

    // Salvar no csv com uma opçao no menu e ao fechar perguntar se deseja salvar
    // (igual vim) criar funçao salve_csv()

/* -------------------------------------------------------------------------------- */
    // HACK: Testes

    // char log_key[1024];
    // char search_key[1024];
    // study_log buffer_arr[MAX_RESULT];
    //
    // printf("Entre para campo de ordenaçao: ");
    // string_input(log_key, sizeof(log_key));
    //
    // printf("Entre o valor de busca: ");
    // string_input(search_key, sizeof(search_key));
    //
    // int found = search_arr (buffer_arr, logs_arr, arr_size, log_key, search_key);
    //
    // printf("Resultado da busca: \n");
    // int x = 0;
    // while (found != 0){
    // printf("%s, %s, %s, %s, %s\n",
    //        buffer_arr[x].ID, buffer_arr[x].subject, buffer_arr[x].topic,
    //        buffer_arr[x].start_date, buffer_arr[x].end_date);
    //
    //     x++;
    //     found--;
    // }
    //
    // printf("Last ID: %s\n", last_ID);
/* -------------------------------------------------------------------------------- */

    free(logs_arr);
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
    int i = 0;

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
            if (column == 0)
            {
                strcpy (logs_arr[i].ID, value);
            }

            if (column == 1)
            {
                strcpy (logs_arr[i].subject, value);
            }

            if (column == 2)
            {
                strcpy (logs_arr[i].topic, value);
            }

            if (column == 3)
            {
                strcpy (logs_arr[i].start_date, value);
            }
            if (column == 4)
            {
                strcpy (logs_arr[i].end_date, value);
            }
            if (column == 5)
            {
                strcpy (logs_arr[i].status, value);
            }

            value = strtok (NULL, ",");
            column++;
        }
        i++;
    }
    return 0;
}
