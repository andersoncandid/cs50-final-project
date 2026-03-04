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
int execute_search (study_log *results_arr, study_log *logs_arr, const size_t arr_size,
                    const char *search_member, const char *search_value);
int save_data (study_log *logs_arr,const size_t arr_size, const char *file_name);

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


    /* --------- Program menu loop --------- */
    // while (1)
    // {
        // char menu_option[DATE_LENGTH] = {0};
        // study_log results_arr[MAX_RESULTS] = {0};
        // char search_member[DATE_LENGTH] = {0};
        // char search_value[ENTRY_LENGTH] = {0};

        // User Menu
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

        // FIX: 1. Add new

        // add_new(&logs_arr, &arr_size, &free_space, last_ID);

        // 2. Edit log status by ID
        // char target_id[DATE_LENGTH];
        // int target_index;
        //
        // printf("Enter log ID: ");
        // string_input (target_id, sizeof (target_id));
        // target_index = search_ID(logs_arr,arr_size, target_id);
        //
        // // Check if the ID was not found
        // if (target_index == - 1)
        // {
        //     continue;
        // }

        // FIX: 2. Find by Struct Key

        // if (edit_log(logs_arr, arr_size, target_index) == 1)
        // {
        //     continue;
        // }

        // Prompt for search member
        // printf("Search by\n  0. ID\n  1. Subject\n  2. Topic\n  3. Start date\n"
        //        "  4. End date\n  5. Return to Menu\n");
        // printf("\nEnter an option [0-5]: ");
        // string_input (search_member, sizeof (search_member));
        //
        // // Validate input
        // while (strlen(search_member) > 1 ||
        //     (search_member[0] < 48 || search_member[0] > 53))
        // {
        //     printf("Invalid option\nEnter an option [0-5]: ");
        //     string_input (search_member, sizeof (search_member));
        // }
        //
        // // Prompt for search value
        // switch (search_member[0])
        // {
        //     case '0':
        //         printf("Enter ID: "); break;
        //     case '1':
        //         printf("Enter Subject: "); break;
        //     case '2':
        //         printf("Enter Topic: "); break;
        //     case '3':
        //         printf("Enter Start date: "); break;
        //     case '4':
        //         printf("Enter End date: "); break;
        //     case '5':
        //         continue;
        //         break;
        //     default:
        //         continue;
        //         break;
        // }
        //
        // string_input (search_value, sizeof (search_value));
        //
        // if (execute_search(results_arr, logs_arr, arr_size,
        //                    search_member, search_value) == 0)
        // {
        //     continue;
        // }

        // FIX: 3. Edit log by ID

        // FIX:  4. Show Unfinished

        // if (execute_search(results_arr, logs_arr, arr_size,
        //                    "5", "In Progress") == 0)
        // {
        //     continue;
        // }

        // FIX: 5. Show Start date by month

        // char mouth_input[DATE_LENGTH];
        // char regex_format[ENTRY_LENGTH];
        //
        // printf("Enter the month [MM]: ");
        // string_input (mouth_input, sizeof (mouth_input));
        //
        //
        // // Building a regex for filter MM in date(YYYY-MM-DD)
        // snprintf(regex_format, sizeof(regex_format), "^[0-9]{4}-%s-[0-9]{2}$",
        //          mouth_input);
        //
        // if (execute_search(results_arr, logs_arr, arr_size,
        //                    "3", regex_format) == 0)
        // {
        //     continue;
        // }

        // FIX: 6. Save Changes >> nao adicionar ao arquivo status == 2 [REMOVED]

            // save_data(logs_arr,arr_size, file_name);
            // continue;

        // FIX: 8. Exit >> Perguntar se deseja salvar

            // save_data(logs_arr,arr_size, file_name);

        //  Nota:  No Readme instruçao de onde e como gerenciar o arquivo salvo
        //  log.csv

        // Salvar no csv com uma opçao no menu e ao fechar perguntar se deseja salvar
        // (igual vim) criar funçao salve_csv()

    // }
/* -------------------------------------------------------------------------------- */
    // HACK: Testes

    // char log_key[1024];
    // char search_key[1024];
    // study_log buffer_arr[MAX_RESULTS];
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
int file_exists (const char *file_name)
{
    struct stat buffer;

    if (stat (file_name, &buffer) == 0)
    {
        return 1; // File exists

    } else {
        return 0;
    }
}

// Number of rows in the file
int count_rows (const char *file_name)
{
    FILE *file = fopen (file_name, "r");
    if (file == NULL)
    {
        printf ("Error: File Not Found!\n");
        return -1;
    }

    int rows = 0;
    char buffer[1024];

    // Reads line by line until the end of the file
    while (fgets(buffer, sizeof(buffer), file))
    {
        // Skip empty or invalid lines
        if (buffer[0] != '\n' && buffer[0] != '\r' && buffer[0] != '\0')
        {
            rows++;
        }
    }

    fclose (file);
    return rows;
}

// Parsing the CSV log file
int csv_parser (study_log *logs_arr, const char *file_name)
{

    FILE *file = fopen (file_name, "r");
    if (file == NULL)
    {
        printf ("Error: The study.csv file could not be opened.\n");
        return -1;
    }

    char buffer[1024];

    int row = 0;
    int column = 0;
    int i = 0;

    // Parsing line by line
    while (fgets (buffer, sizeof (buffer), file))
    {
        // Remove \n or \r from the end of the line
        buffer[strcspn(buffer, "\r\n")] = '\0';

        // Skip empty lines
        if (buffer[0] == '\0')
        {
            continue; 
        }

        column = 0;
        row++;

        // Skip first row
        if (row == 1)
            continue;

        // Pointers for comma separation
        char *start = buffer;
        char *end;

        // TODO: Enteder essa parte
        while (start != NULL)
        {
            // Procura a próxima vírgula a partir do 'start'
            end = strchr(start, ',');

            // Se encontrou uma vírgula, substitui por '\0' para "cortar" a string ali
            if (end != NULL)
            {
                *end = '\0'; 
            }

            // O ponteiro 'start' agora contém o valor isolado da coluna atual
            // (Mesmo se for vazio, ele conterá "")
            if (column == 0)
            {
                strcpy (logs_arr[i].ID, start);
            }

            else if (column == 1)
            {
                strcpy (logs_arr[i].subject, start);
            }

            else if (column == 2)
            {
                strcpy (logs_arr[i].topic, start);
            }

            else if (column == 3)
            {
                strcpy (logs_arr[i].start_date, start);
            }

            else if (column == 4)
            {
                strcpy (logs_arr[i].end_date, start);
            }

            else if (column == 5)
            {
                strcpy (logs_arr[i].status, start);
            }

            // Prepara para a próxima iteração
            if (end != NULL)
            {
                start = end + 1; // Avança o 'start' para logo após a vírgula que cortamos
            }
            else
            {
                start = NULL; // Chegou no fim da linha (não tem mais vírgulas)
            }

            column++;
        }
            i++;
    }
    return 0;
}

// Execute search and display results
int execute_search (study_log *results_arr, study_log *logs_arr, const size_t arr_size,
                    const char *search_member, const char *search_value)
{
    int results_count;

    results_count = search_arr(results_arr, logs_arr, arr_size,
                               search_member, search_value);

    if (results_count == 0)
    {
        printf("Nothing found!\n");
        return 0;
    }

    // Display results
    printf("\nShowing the last %d match(es):", results_count);
    printf("\n---------------------------------------- Search Results ---------"
           "-------------------------------\n");
    printf(BLUE "\n%-5s   %-15s   %-35s   %-10s   %-10s   %s\n" RESET,
           "ID", "Subject", "Topic", "Start Date", "End Date", "Status");
    for (int c = 0; c < results_count; c++)
    {
        printf("%-5s | %-15s | %-35s | %-10s | %-10s | %s",
           results_arr[c].ID, results_arr[c].subject, results_arr[c].topic,
               results_arr[c].start_date, results_arr[c].end_date,
               results_arr[c].status);
    }
    printf("\n");

    return 0;
}

// Save data in the userdata CSV file
int save_data (study_log *logs_arr,const size_t arr_size, const char *file_name)
{
    FILE *file = fopen (file_name, "w");
    if (file == NULL)
    {
        printf ("Error: The study.csv file could not be opened.\n");
        return -1;
    }

    fprintf(file, "%s,%s,%s,%s,%s,%s\n", "ID", "Subject", "Topic",
            "Start Date", "End Date", "Status");

    for (int i = 0; i < (int)arr_size; i++)
    {
        // Skipping status  == delete Log marked for removal
        if (strcmp(logs_arr[i].status, "delete") == 0)
        {
            continue;
        }

        // Writing to a file in CSV format.
         fprintf(file, "%s,%s,%s,%s,%s,%s\n", logs_arr[i].ID, logs_arr[i].subject,
                 logs_arr[i].topic, logs_arr[i].start_date,
                 logs_arr[i].end_date, logs_arr[i].status);
    }

    fclose(file);

    printf("Data Saved in %s\n", file_name);
    return 0;
}
