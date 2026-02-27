// Declares the program's functionality
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

// Creating an array of helper function pointers
comp_func ptr_arr[5] = {&id_cmp, &subj_cmp, &top_cmp, &start_cmp, &end_cmp};

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
        default:
            break;
    }
}

int search_arr (study_log *buffer_arr, study_log *logs_arr, size_t arr_size,
               const char *log_key, char *search_key)
{
    regex_t reegex;
    int n = 0;

    // Compiling Regex
    if (regcomp(&reegex, search_key, REG_ICASE) != 0)
    {
        return 0; // Compilation error
    }

    // Loop until end of array or reach max of found values
    for (int i = 0; i < (int)arr_size && n < 30; i++)
    {
        const char *target_value = NULL;

        // Get the value from logs_arr that corresponds to the log_key
        switch (*log_key)
        {
            case '0':
                target_value = logs_arr[i].ID;
                break;
            case '1':
                target_value = logs_arr[i].subject;
                break;
            case '2':
                target_value = logs_arr[i].topic;
                break;
            case '3':
                target_value = logs_arr[i].start_date;
                break;
            case '4':
                target_value = logs_arr[i].end_date;
                break;
            default:
                break;
        }

        // Apply regex on a valid target value
        if (target_value != NULL)
        {
            if (regexec(&reegex, target_value, 0, NULL, 0) == 0) {
                buffer_arr[n] = logs_arr[i]; // Pattern found
                n++;
            }
        }
    }

    regfree(&reegex);

    sort_arr (buffer_arr, n, "0");
    return n;
}

// Add new entry
// int add_new (study_log *logs_arr, size_t arr_size, int *free_space, char *last_ID) {
//     // char buffer[ENTRY_LENGTH];
//     char ID_key = '1'; //ID
//
//     arr_search(logs_arr,arr_size, &ID_key);
//     char *last_ID = logs_arr[*arr_size - 1].ID;
//
//     printf("%s\n", last_ID);
//     // TODO: Initialize with empty strings.
//     //       strcpy (logs_arr->subject, "");
//
//     // printf ("Enter the Subject:\n");
//     // string_input (buffer, sizeof (buffer));
//     // strcpy (logs_arr->subject, buffer);
//
//     return 0;
// }
