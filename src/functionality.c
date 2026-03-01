// Declares the program's functionality
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "definitions.h"

// Safe string handling
int string_input (char *buffer, size_t buffer_size)
{
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

    return 0;
}

// String comparison helper functions
int id_cmp (const void *a, const void *b)
{
    const study_log *aa = (const study_log *)a;
    const study_log *bb = (const study_log *)b;

    return strcmp (aa->ID, bb->ID);
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

// Sorting logs_arr
// NOTE: *sort_field com menu numerico: 0-ID,1-subj,2-top,3-star,4-end
// Se optar pelo input de termo, usar um switch para termo == log_key(numerico)
void sort_arr (study_log *logs_arr, size_t arr_size, const char *log_key)
{
    // Sorting according to the appropriate field
    switch (*log_key)
    {
        case '0':
            qsort(logs_arr, arr_size, sizeof(study_log), ptr_arr[0]);
            break;
        case '1':
            qsort(logs_arr, arr_size, sizeof(study_log), ptr_arr[1]);
            break;
        case '2':
            qsort(logs_arr, arr_size, sizeof(study_log), ptr_arr[2]);
            break;
        case '3':
            qsort(logs_arr, arr_size, sizeof(study_log), ptr_arr[3]);
            break;
        case '4':
            qsort(logs_arr, arr_size, sizeof(study_log), ptr_arr[4]);
            break;
        case '5':
            qsort(logs_arr, arr_size, sizeof(study_log), ptr_arr[5]);
            break;
        default:
            break;
    }
}

int search_arr (study_log *buffer_arr, study_log *logs_arr, size_t arr_size,
               const char *log_key, char *search_key)
{
    regex_t reegex;
    int n = 0;
    int last_index = (int)arr_size - 1;

    // Compiling Regex
    if (regcomp(&reegex, search_key, REG_ICASE) != 0)
    {
        return 0; // Compilation error
    }

    // Retrieves the latest entries as search results
    sort_arr (logs_arr, n, "0");

    // Loop until end of array or reach max of found values
    for (int i = 0; i < (int)arr_size && n < MAX_RESULT; i++)
    {
        const char *target_value = NULL;

        // Get the value from logs_arr that corresponds to the log_key
        switch (*log_key)
        {
            case '0':
                target_value = logs_arr[last_index - i].ID;
                break;
            case '1':
                target_value = logs_arr[last_index - i].subject;
                break;
            case '2':
                target_value = logs_arr[last_index - i].topic;
                break;
            case '3':
                target_value = logs_arr[last_index - i].start_date;
                break;
            case '4':
                target_value = logs_arr[last_index - i].end_date;
                break;
            case '5':
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
                buffer_arr[n] = logs_arr[last_index - i]; // Pattern found
                n++;
            }
        }
    }

    regfree(&reegex);

    sort_arr (buffer_arr, n, "0");
    return n; // n == 0, Nothing found.
}

// Validate date input format YYYY-MM-DD
int valid_date (char *date)
{
    int len = strlen(date);

    // Validate the size
    if (len != 10)
    {
        return 1;
    }

    //  Validade hyphens
    if (date[4] != 45 || date[7] != 45)
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

    // Month tens digit > 1 and days > 3
    if (date[5] > 49 && date[8] > 51)
    {
        return 2;
    }

    // MM > 12 and DD > 31
    if ((date[5] == 49 && date[6] > 50) || (date[8] == 51 && date[9] > 49))
    {
        return 2;
    }

    return 0;
}

// Add new entry
int add_new (study_log **logs_arr, size_t *arr_size, size_t *free_space,
              char *last_ID)
{
    char buffer[ENTRY_LENGTH];
    char confirm = 'n';

    do {
        printf("\n--------------- Add New Log ---------------\n");

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

        int current_index = *arr_size;

        // Add new ID
        int int_ID = atoi(last_ID);
        sprintf(buffer, "%d", int_ID);
        strcpy ((*logs_arr)[current_index].ID, buffer);

        // Add new subject
        printf("Enter subject: ");
        string_input (buffer, sizeof (buffer));
        strcpy ((*logs_arr)[current_index].subject, buffer);

        // Add new topic
        printf("Enter topic: ");
        string_input (buffer, sizeof (buffer));
        strcpy ((*logs_arr)[current_index].topic, buffer);

        // Add new start_date
        printf("Enter start date [YYYY-MM-DD]: ");
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

            printf("Enter start date: ");
            string_input (buffer, sizeof (buffer));
            validate_date = valid_date(buffer);
        }

        strcpy ((*logs_arr)[current_index].start_date, buffer);

        // Add new end_date
        printf("Enter end date [YYYY-MM-DD]: ");
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

            printf("Enter end date: ");
            string_input (buffer, sizeof (buffer));
            validate_date = valid_date(buffer);
        }

        strcpy ((*logs_arr)[current_index].end_date, buffer);

        // Add new status
        printf("Status [0: In Progress, 1: Completed]: ");
        string_input (buffer, sizeof (buffer));

        // Validate status input
        while (strlen(buffer) > 1 || (buffer[0] != 48 && buffer[0] != 49))
        {
            printf("Invalid input. Enter:"
                   " \n  [0] for In Progress\n  [1] for Completed");
            printf("\nStatus: ");
            string_input (buffer, sizeof (buffer));
        }

        strcpy ((*logs_arr)[current_index].status, buffer);

        *free_space -= 1;
        *arr_size += 1;

        // TODO: Check entrys
        printf("\nAdd another entry? (y/n): ");

        // If input is not empty
        if (string_input (buffer, sizeof (buffer)) != 2)
        {
            confirm = tolower(buffer[0]);
        }

    } while (confirm == 'y');

    return 0;
}
