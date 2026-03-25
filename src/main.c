/*******************************************************************************
  CS50x Final Project
  Title: Study Log
  Author: Anderson Reinaldo Candido
 ******************************************************************************/

#include <ctype.h>
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
void main_menu ();
int execute_search (study_log *results_arr, study_log *logs_arr, const size_t arr_size,
                    const char *search_member, const char *search_value);
int save_data (study_log *logs_arr,const size_t arr_size, const char *file_name);
void open_csv_file (const char *file_name);

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
    sort_arr(logs_arr, arr_size, "1");

    strcpy(last_ID, logs_arr[arr_size - 1].ID);


    /* --------- Program menu loop --------- */
    int loop = 1;
    int startup = 1;

    while (loop)
    {
        // Initialize search buffers and variables
        char menu_opt[DATE_LENGTH] = {0};
        study_log results_arr[MAX_RESULTS] = {0};
        char search_member[DATE_LENGTH] = {0};
        char search_value[ENTRY_LENGTH] = {0};
        char target_id[DATE_LENGTH] = {0};
        int target_index = 0;
        char year_input[DATE_LENGTH] = {0};
        char mouth_input[DATE_LENGTH] = {0};
        char regex_format[ENTRY_LENGTH] = {0};
        char confirm_save[DATE_LENGTH] = {0};

        // Display menu on startup
        if (startup == 1)
        {
            main_menu();
            startup = 0;
        }

        // Prompt user for menu selection
        printf("\nSelect an option [1-8, 0 for menu]: ");
        string_input (menu_opt, sizeof (menu_opt));

        // Validate input
        while (strlen(menu_opt) > 1 || (menu_opt[0] < '0' || menu_opt[0] > '8'))
        {
            printf("Invalid option\nSelect an option [1-8, 0 for menu]: ");
            string_input (menu_opt, sizeof (menu_opt));
        }

        switch (menu_opt[0])
        {
            // Show menu options
            case '0':
                main_menu();
            break;

            // New entry option
            case '1':
                add_new(&logs_arr, &arr_size, &free_space, last_ID);
            break;

            // Search option
            case '2':
                printf("Search by\n"
                       "  1. ID\n"
                       "  2. Subject\n"
                       "  3. Topic\n"
                       "  4. Start date\n"
                       "  5. End date\n"
                       "  6. Return to Menu\n");
                printf("Enter an option [1-6]: ");
                string_input (search_member, sizeof (search_member));

                // Validate input
                while (strlen(search_member) > 1 ||
                    (search_member[0] < '1' || search_member[0] > '6'))
                {
                    printf("Invalid option\nEnter an option [1-6]: ");
                    string_input (search_member, sizeof (search_member));
                }

                switch (search_member[0])
                {
                    case '1':
                        printf("ID: "); break;
                    case '2':
                        printf("Subject: "); break;
                    case '3':
                        printf("Topic: "); break;
                    case '4':
                        printf("Start date: "); break;
                    case '5':
                        printf("End date: "); break;
                    case '6':
                        continue;
                    default:
                        continue;
                }

                string_input (search_value, sizeof (search_value));

                if (execute_search(results_arr, logs_arr, arr_size,
                                   search_member, search_value) == 0)
                {
                    continue;
                }
            break;

            // Edit by ID option
            case '3':
                printf("Entry ID: ");
                string_input (target_id, sizeof (target_id));
                target_index = search_ID(logs_arr,arr_size, target_id);

                // Check if the ID was not found
                if (target_index == - 1)
                {
                    continue;
                }
                if (edit_log(logs_arr, arr_size, target_index) == 1)
                {
                    continue;
                }
            break;

            // View In Progress option
            case '4':
                if (execute_search(results_arr, logs_arr, arr_size,
                                   "6", "In Progress") == 0)
                {
                    continue;
                }
            break;

            // View start mouth option
            case '5':
                printf("Year [YYYY]: ");
                string_input (year_input, sizeof (year_input));

                printf("Month [MM]: ");
                string_input (mouth_input, sizeof (mouth_input));

                // Building a regex for filter MM in date(YYYY-MM-DD)
                snprintf(regex_format, sizeof(regex_format),
                         "^%s-%s-[0-9]{2}$", year_input, mouth_input);

                if (execute_search(results_arr, logs_arr, arr_size,
                                   "4", regex_format) == 0)
                {
                    continue;
                }
            break;

            // Save data option
            case '6':
                printf("\n");
                save_data(logs_arr,arr_size, file_name);
                continue;
            break;

            // Open CSV in external program option
            case '7':
                open_csv_file(file_name);
                continue;
            break;

            // Save and exit option
            case '8':
                printf("\nConfirm: Save data in CSV file? (y/n): ");
                string_input (confirm_save, sizeof (confirm_save));

                if (strlen(confirm_save) == 1 && tolower(confirm_save[0]) == 'y')
                {
                    save_data(logs_arr,arr_size, file_name);
                }
                else
                {
                    printf("  Data not saved!\n");
                }

                loop = 0;
            break;

            default:
                loop = 0;
            break;
        }

    }

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

// Get number of rows in the CSV file
// NOTE: Added '\r' check for Windows CRLF compatibility (suggested by Gemini)
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

        char *start = buffer;
        char *end;

        while (start != NULL)
        {
            // Find the position of the next comma starting from "start"
            // and return its address in "end".
            end = strchr(start, ',');

            // Replace comma for NULL char
            if (end != NULL)
            {
                *end = '\0'; 
            }

            // Copying the string to the current column
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

            // For next string in the row
            if (end != NULL)
            {
                start = end + 1; // Next address immediately after "end"
            }
            else
            {
                start = NULL; // End of the line
            }

            column++;
        }
            i++;
    }

    fclose(file);

    return 0;
}

// Main menu interface
void main_menu ()
{
    printf("\n================================\n%20s\n"
           "================================\n", "STUDY LOG");
    printf(" 1. Add new entry\n"
           " 2. Search study entries\n"
           " 3. Edit study entry by ID\n"
           " 4. View 'In Progress' studies\n"
           " 5. View studies by start month\n"
           " 6. Save changes to CSV\n"
           " 7. Open CSV in external program\n"
           " 8. Save and Exit\n");
    printf("================================\n");
}

// Search for values in logs array and display formated results
int execute_search (study_log *results_arr, study_log *logs_arr, const size_t arr_size,
                    const char *search_member, const char *search_value)
{
    int results_count;

    results_count = search_arr(results_arr, logs_arr, arr_size,
                               search_member, search_value);

    if (results_count == 0)
    {
        printf("\n  Nothing found!\n\n");
        return 0;
    }

    // Display results
    printf("\nShowing the last %d match(es):", results_count);

    printf("\n----------------------------"
           "------------ Search Results ---"
           "-------------------------------------\n");

    printf(BLUE "%-5s | %-15s | %-35s | %-10s | %-10s | %s\n" RESET,
           "ID", "Subject", "Topic", "Start Date", "End Date", "Status");

    for (int c = 0; c < results_count; c++)
    {
        printf("%-5s | %-15s | %-35s | %-10s | %-10s | %s\n",
               results_arr[c].ID,
               results_arr[c].subject,
               results_arr[c].topic,
               results_arr[c].start_date,
               results_arr[c].end_date,
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
        printf ("Error: The study.csv file could not be opened for save.\n");
        return -1;
    }

    fprintf(file, "%s,%s,%s,%s,%s,%s\n",
            "ID",
            "Subject",
            "Topic",
            "Start Date",
            "End Date",
            "Status");

    for (int i = 0; i < (int)arr_size; i++)
    {
        // Skipping status  == delete Log marked for removal
        if (strcmp(logs_arr[i].status, "delete") == 0)
        {
            continue;
        }

        // Writing to a file in CSV format.
         fprintf(file, "%s,%s,%s,%s,%s,%s\n",
                 logs_arr[i].ID,
                 logs_arr[i].subject,
                 logs_arr[i].topic,
                 logs_arr[i].start_date,
                 logs_arr[i].end_date,
                 logs_arr[i].status);
    }

    fclose(file);

    printf("Data Saved in %s\n\n", file_name);
    return 0;
}

// Open a CSV file in the user's preferred application
// NOTE: Cross-platform portability logic adapted from chat with Gemini
void open_csv_file (const char *file_name)
{
    char command[256];

    // For Windows
    #ifdef _WIN32
        sprintf(command, "start %s", file_name);

    // For Mac
    #elif __APPLE__
        sprintf(command, "open %s", file_name);

    // For Linux
    #else
        sprintf(command, "xdg-open %s &", file_name);

    #endif

    // Execute the command to open the file
    system(command);
}
