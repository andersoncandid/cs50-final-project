// Declares the program's functionality
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "definitions.h"

// Prototype
void trim_string(char *str);
int id_cmp (const void *a, const void *b);
int subj_cmp (const void *a, const void *b);
int top_cmp (const void *a, const void *b);
int start_cmp (const void *a, const void *b);
int end_cmp (const void *a, const void *b);
int status_cmp (const void *a, const void *b);
int valid_date (const char *date);

// Trimming white spaces from a string
// NOTE: Adapted from: https://www.delftstack.com/howto/c/trim-string-in-c/
void trim_string(char *str)
{
    // Error check
    if (str == NULL)
    {
        return;
    }

    int len = strlen(str);
    if (len == 0)
    {
        return; // Empty string
    }

    int start = 0, end = len - 1;

    // Loop from start to the first of the non null chars
    while (isspace((unsigned char)str[start]))
    {
        start++;
    }

    // Loop backwards in the string reaching the last of non null chars
    while (end > start && isspace((unsigned char)str[end]))
    {
        end--;
    }

    // Move the string and place null terminator
    if (start > 0 || end < (len - 1))
    {
        memmove(str, str + start, end - start + 1);
        str[end - start + 1] = '\0';
    }
}

// Safe string handling
// NOTE: Debugged and optimized with Gemini
int string_input (char *buffer, const size_t buffer_size)
{
    // Initialize buffer
    buffer[0] = '\0';

    if (fgets (buffer, buffer_size, stdin) == NULL)
    {
        return 1; // Input error
    }

    // Check if the input exceeds the size
    if (strchr (buffer, '\n') != NULL)
    {
        // If the \n was found, the input fit in the buffer
        // Remove trailing newline
        buffer[strcspn (buffer, "\n")] = '\0';
    } else {

        // Clean stdin
        int c;
        while ((c = getchar ()) != '\n' && c != EOF)
            ;
    }

    // Check for empty input
    if (strlen (buffer) == 0)
    {
        return 2;
    }

    // Trim input
    trim_string(buffer);

    return 0;
}

/*
NOTE: Application of an array of function
pointers for comparison functions,
suggested by Gemini.
*/

// String comparison helper functions
int id_cmp (const void *a, const void *b)
{
    const study_log *aa = (const study_log *)a;
    const study_log *bb = (const study_log *)b;

    // Convert strig to int
    int id_a = atoi(aa->ID);
    int id_b = atoi(bb->ID);

    // Numeric Comparision
    if (id_a < id_b) return -1;
    if (id_a > id_b) return 1;
    return 0;
}

int subj_cmp (const void *a, const void *b)
{
    const study_log *aa = (const study_log *)a;
    const study_log *bb = (const study_log *)b;

    return strcmp (aa->subject, bb->subject);
}

int top_cmp (const void *a, const void *b)
{
    const study_log *aa = (const study_log *)a;
    const study_log *bb = (const study_log *)b;

    return strcmp (aa->topic, bb->topic);
}

int start_cmp (const void *a, const void *b)
{
    const study_log *aa = (const study_log *)a;
    const study_log *bb = (const study_log *)b;

    return strcmp (aa->start_date, bb->start_date);
}

int end_cmp (const void *a, const void *b)
{
    const study_log *aa = (const study_log *)a;
    const study_log *bb = (const study_log *)b;

    return strcmp (aa->end_date, bb->end_date);
}

int status_cmp (const void *a, const void *b)
{
    const study_log *aa = (const study_log *)a;
    const study_log *bb = (const study_log *)b;

    return strcmp (aa->status, bb->status);
}

// Creating an array of helper function pointers
comp_func ptr_arr[6] = {&id_cmp, &subj_cmp, &top_cmp, &start_cmp, &end_cmp, &status_cmp};

// Sorting array by value
void sort_arr (study_log *array, const size_t arr_size, const char *sort_value)
{
    // Sorting according to the appropriate field
    switch (sort_value[0])
    {
        case '1':
            qsort(array, arr_size, sizeof(study_log), ptr_arr[0]);
            break;
        case '2':
            qsort(array, arr_size, sizeof(study_log), ptr_arr[1]);
            break;
        case '3':
            qsort(array, arr_size, sizeof(study_log), ptr_arr[2]);
            break;
        case '4':
            qsort(array, arr_size, sizeof(study_log), ptr_arr[3]);
            break;
        case '5':
            qsort(array, arr_size, sizeof(study_log), ptr_arr[4]);
            break;
        case '6':
            qsort(array, arr_size, sizeof(study_log), ptr_arr[5]);
            break;
        default:
            break;
    }
}

// Search in logs_arr per member and value
int search_arr (study_log *results_arr, study_log *logs_arr, const size_t arr_size,
               const char *search_member, const char *search_value)
{
     /*
     NOTE: Utilized Gemini to troubleshoot and polish
     regex patterns for improved input validation.
     */

    regex_t reegex;
    int n = 0;
    int last_index = (int)arr_size - 1;

    // Compiling Regex
    if (regcomp(&reegex, search_value, REG_EXTENDED | REG_ICASE) != 0)
    {
        return 1; // Compilation error
    }

    // Sort by ID for retrieves the latest entries as search results
    sort_arr (logs_arr, arr_size, "1");

    // Loop until end of array or reach max of found values
    for (int i = 0; i < (int)arr_size && n < MAX_RESULTS; i++)
    {
        const char *target_value = NULL;

        // Skipping status marked for removal
        if (strcmp(logs_arr[last_index - i].status, "delete") == 0)
        {
            continue;
        }

        // Get the value from logs_arr that corresponds to the search_value
        switch (*search_member)
        {
            case '1':
                target_value = logs_arr[last_index - i].ID;
                break;
            case '2':
                target_value = logs_arr[last_index - i].subject;
                break;
            case '3':
                target_value = logs_arr[last_index - i].topic;
                break;
            case '4':
                target_value = logs_arr[last_index - i].start_date;
                break;
            case '5':
                target_value = logs_arr[last_index - i].end_date;
                break;
            case '6':
                target_value = logs_arr[last_index - i].status;
                break;
            default:
                break;
        }

        // Apply regex on a valid target value
        if (target_value != NULL)
        {
            if (regexec(&reegex, target_value, 0, NULL, 0) == 0)
            {
                results_arr[n] = logs_arr[last_index - i]; // Pattern found
                n++;
            }
        }
    }

    regfree(&reegex);

    if (n > 0)
    {
        size_t results_size = n;
        sort_arr (results_arr, results_size, "1");
    }

    return n; // n == 0, Nothing found
}

// Validate date input format YYYY-MM-DD
int valid_date (const char *date)
{
    int len = strlen(date);

    // Validate the size
    if (len != 10)
    {
        return 1;
    }

    //  Validade hyphens
    if (date[4] != '-' || date[7] != '-')
    {
        return 1;
    }

    // Check if there are only digits
    for (int i = 0; i < len; i++)
    {
        if (i == 4 || i == 7)
        {
            continue;
        }
        if (isdigit(date[i]) == 0)
        {
            return 1;
        }
    }

    // Month tens digit > 1 or days > 3
    if (date[5] > '1' || date[8] > '3')
    {
        return 2;
    }

    // Month entry[MM] > 12 or Day entry[DD] > 31
    if ((date[5] == '1' && date[6] > '2') || (date[8] == '3' && date[9] > '1'))
    {
        return 2;
    }

    return 0;
}

// Add new entry
int add_new (study_log **logs_arr, size_t *arr_size, size_t *free_space,
              char *last_ID)
{
    study_log temp;
    char buffer[ENTRY_LENGTH];
    char confirm = 'n';

    do {
        printf("-------------- Add New Entry --------------\n");

        // Verify if logs_arr is full
        if (*free_space <= 0)
        {
            *free_space = 100;
            size_t new_size = *arr_size + *free_space;

            // Resize logs_arr
            study_log *tmp = realloc(*logs_arr, (new_size) * sizeof(study_log));
            if (tmp == NULL)
            {
                return 1;
            }
            *logs_arr = tmp;

        }

        // Add new ID
        int new_ID = (atoi(last_ID)) + 1;
        sprintf(buffer, "%d", new_ID);
        strcpy (temp.ID, buffer);

        // Add new subject
        printf("Subject: ");
        string_input (buffer, sizeof (buffer));
        strcpy (temp.subject, buffer);

        // Add new topic
        printf("Topic: ");
        string_input (buffer, sizeof (buffer));
        strcpy (temp.topic, buffer);

        // Add new start_date
        printf("Start date [YYYY-MM-DD]: ");
        string_input (buffer, sizeof (buffer));
        int validate_date = valid_date(buffer);

        // Check if the input is in the correct format
        while (validate_date != 0)
        {
            if (validate_date == 1)
            {
                printf("Invalid format\n"
                       "  Use: YYYY-MM-DD (e.g., 2026-03-01)\n");
            }
            if (validate_date == 2)
            {
                printf("Invalid date values\n"
                       "  (MM: 01-12, DD: 01-31)\n");
            }

            printf("Start date: ");
            string_input (buffer, sizeof (buffer));
            validate_date = valid_date(buffer);
        }

        strcpy (temp.start_date, buffer);

        // Add new end_date
        printf("End date [YYYY-MM-DD]: ");
        string_input (buffer, sizeof (buffer));
        validate_date = valid_date(buffer);

        // Check if the input is in the correct format
        while (validate_date != 0)
        {
            if (validate_date == 1)
            {
                printf("Invalid format\n"
                       "  Use: YYYY-MM-DD (e.g., 2026-03-01)\n");
            }
            if (validate_date == 2)
            {
                printf("Invalid date values\n"
                       "  (MM: 01-12, DD: 01-31)\n");
            }

            printf("End date: ");
            string_input (buffer, sizeof (buffer));
            validate_date = valid_date(buffer);
        }

        strcpy (temp.end_date, buffer);

        // Add new status
        printf("Status [0: In Progress, 1: Completed]: ");
        string_input (buffer, sizeof (buffer));

        // Validate status input
        while (strlen(buffer) > 1 || (buffer[0] != '0' && buffer[0] != '1'))
        {
            printf("Invalid input. Enter:"
                   " \n  [0] for In Progress\n  [1] for Completed");
            printf("\nStatus: ");
            string_input (buffer, sizeof (buffer));
        }

        if (buffer[0] == '0')
        {
            strcpy (temp.status, "In Progress");
        }
        if (buffer[0] == '1')
        {
            strcpy (temp.status, "Completed");
        }

        // Confirming the entry before updating logs_arr
        printf(BLUE "\n%-5s | %-15s | %-35s | %-10s | %-10s | %s\n" RESET,
               "ID", "Subject", "Topic", "Start Date", "End Date", "Status");
        printf("%-5s | %-15s | %-35s | %-10s | %-10s | %s\n",
               temp.ID,
               temp.subject,
               temp.topic,
               temp.start_date,
               temp.end_date,
               temp.status);

        printf("\nConfirm entry? (y/n): ");
        string_input (buffer, sizeof (buffer));

            // Validating the confirmation
            if (strlen(buffer) == 1 && tolower(buffer[0]) == 'y')
            {
                strcpy(last_ID, temp.ID); // Update last_ID

                strcpy ((*logs_arr)[*arr_size].ID, temp.ID);
                strcpy ((*logs_arr)[*arr_size].subject, temp.subject);
                strcpy ((*logs_arr)[*arr_size].topic, temp.topic);
                strcpy ((*logs_arr)[*arr_size].start_date, temp.start_date);
                strcpy ((*logs_arr)[*arr_size].end_date, temp.end_date);
                strcpy ((*logs_arr)[*arr_size].status, temp.status);

                *free_space -= 1;
                *arr_size += 1;
            }
            else
            {
                printf("  Entry not saved!\n");
            }

        // Assign empty string to temp variable
        temp.ID[0] = '\0';
        temp.subject[0] = '\0';
        temp.topic[0] = '\0';
        temp.start_date[0] = '\0';
        temp.end_date[0] = '\0';
        temp.status[0] = '\0';

        printf("Add another entry? (y/n): ");
        string_input (buffer, sizeof (buffer));

        if (strlen(buffer) == 1 && tolower(buffer[0]) == 'y')
        {
            confirm = tolower(buffer[0]);
        }

    } while (confirm == 'y');

    return 0;
}

// Find target ID for edit function
int search_ID (const study_log *logs_arr, const size_t arr_size,
               const char *target_ID)
{
    for (int i = 0; i < (int)arr_size; i++)
    {
        if (strcmp(logs_arr[i].ID, target_ID) == 0)
        {
            return i;
        }

    }

    printf("ID %s not found\n", target_ID);
    return -1;
}

// Edit end date, status or delete log
int edit_log (study_log *logs_arr, const size_t arr_size, const int target_index)
{
    study_log temp;
    char buffer[ENTRY_LENGTH];
    int validate_date;

    // Copy taget log to temp struct
    strcpy(temp.ID, logs_arr[target_index].ID);
    strcpy(temp.subject, logs_arr[target_index].subject);
    strcpy(temp.topic, logs_arr[target_index].topic);
    strcpy(temp.start_date, logs_arr[target_index].start_date);
    strcpy(temp.end_date, logs_arr[target_index].end_date);
    strcpy(temp.status, logs_arr[target_index].status);

    // Display target log
    printf("\n------------------------------------------ Entry Info ----"
           "--------------------------------------\n");
    printf(BLUE "%-5s | %-15s | %-35s | %-10s | %-10s | %s\n" RESET,
           "ID", "Subject", "Topic", "Start Date", "End Date", "Status");
    printf("%-5s | %-15s | %-35s | %-10s | %-10s | %s\n",
           temp.ID,
           temp.subject,
           temp.topic,
           temp.start_date,
           temp.end_date,
           temp.status);

    // Get edit options
    printf("\n=== Edit options ===\n"
           "1. Edit end date\n"
           "2. Edit Status\n"
           "3. Delete Entry\n"
           "4. Return to menu\n"
           "\nSelect an edit option [1-4]: ");
    string_input (buffer, sizeof (buffer));

    // Validate input
    if (strlen(buffer) > 1 || (buffer[0] < '1' || buffer[0] > '4'))
    {
        printf("Invalid option\n");
        return 1;
    }

    switch (buffer[0])
    {
        case '1':
            printf("New end date [YYYY-MM-DD]: ");
            string_input (buffer, sizeof (buffer));
            validate_date = valid_date(buffer);

            // Check if the input is in the correct format
            while (validate_date != 0)
            {
                if (validate_date == 1)
                {
                    printf("Invalid format\n"
                           "  Use: YYYY-MM-DD (e.g., 2026-03-01)\n");
                }
                if (validate_date == 2)
                {
                    printf("Invalid date values\n"
                           "  (MM: 01-12, DD: 01-31)\n");
                }

                printf("New end date: ");
                string_input (buffer, sizeof (buffer));
                validate_date = valid_date(buffer);
            }

            strcpy (temp.end_date, buffer);
        break;

        case '2':
            printf("  [0] for In Progress\n  [1] for Completed");
            printf("\nNew status: ");
            string_input (buffer, sizeof (buffer));

            // Validate status input
            while (strlen(buffer) > 1 || (buffer[0] != '0' && buffer[0] != '1'))
            {
                printf("Invalid input. Enter:"
                       " \n  [0] for In Progress\n  [1] for Completed");
                printf("\nNew status: ");
                string_input (buffer, sizeof (buffer));
            }

            if (buffer[0] == '0')
            {
                strcpy (temp.status, "In Progress");
            }
            if (buffer[0] == '1')
            {
                strcpy (temp.status, "Completed");
            }
        break;

        case '3':
            printf("\nConfirm: Delete Entry? (y/n): ");
            string_input (buffer, sizeof (buffer));

            if (strlen(buffer) == 1 && tolower(buffer[0]) == 'y')
            {
                // [status=2] to remove
                strcpy(temp.status, "delete");

                printf("  Entry deleted!\n");
            }
            else
            {
                printf("  Entry not deleted!\n");
            }

        break;

        case '4':
            break;

        default:
            break;
    }

    // Update logs array
    strcpy(logs_arr[target_index].ID, temp.ID);
    strcpy(logs_arr[target_index].subject, temp.subject);
    strcpy(logs_arr[target_index].topic, temp.topic);
    strcpy(logs_arr[target_index].start_date, temp.start_date);
    strcpy(logs_arr[target_index].end_date, temp.end_date);
    strcpy(logs_arr[target_index].status, temp.status);

    return 0;
}

