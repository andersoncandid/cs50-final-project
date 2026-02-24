// Declares the program's functionality

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "definitions.h"

// Safe string handling
int string_input (char *buffer, size_t buffer_size) {
    if (fgets (buffer, buffer_size, stdin) == NULL) {
        return 1; // Input error
    }

    // Check if the input exceeds the size
    if (strchr (buffer, '\n') != NULL) {

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
    if (strlen (buffer) == 0) {
        return 2;
    }

    return 0;
}

// String comparison helper functions
int id_cmp (const void *a, const void *b) {
    const study_log *aa = (const study_log *)a;
    const study_log *bb = (const study_log *)b;

    return strcmp (aa->ID, bb->ID);
}
int subj_cmp (const void *a, const void *b) {
    const study_log *aa = (const study_log *)a;
    const study_log *bb = (const study_log *)b;

    return strcmp (aa->subject, bb->subject);
}
int top_cmp (const void *a, const void *b) {
    const study_log *aa = (const study_log *)a;
    const study_log *bb = (const study_log *)b;

    return strcmp (aa->topic, bb->topic);
}
int start_cmp (const void *a, const void *b) {
    const study_log *aa = (const study_log *)a;
    const study_log *bb = (const study_log *)b;

    return strcmp (aa->start_date, bb->start_date);
}
int end_cmp (const void *a, const void *b) {
    const study_log *aa = (const study_log *)a;
    const study_log *bb = (const study_log *)b;

    return strcmp (aa->end_date, bb->end_date);
}

// Creating an array of helper function pointers
comp_func ptr_arr[5] = {&id_cmp, &subj_cmp, &top_cmp, &start_cmp, &end_cmp};

// Sorting logs_arr
char arr_sort (study_log *logs_arr, int *arr_size, char *sort_field) {
// De acordo com o sort_field usar uma comp_func apropriada
    //https://www.geeksforgeeks.org/c/array-of-pointers-in-c/

    // Sorting array
}

// TODO: Buscando na logs array > search function

// Add new entry
int add_new (study_log *logs_arr, int *arr_size, int *free_space) {
    char buffer[ENTRY_LENGTH];

    // Find the first empty index at the end of the array
    int tail_index = (*arr_size) - (*free_space);

    // TODO: Usar o search para encontrar o ultimo ID para adicionar o próximo

    // TODO: Initialize with empty strings.
    //       strcpy (logs_arr->subject, "");

    printf ("Enter the Subject:\n");
    string_input (buffer, sizeof (buffer));
    strcpy (logs_arr->subject, buffer);

    return 0;
}
