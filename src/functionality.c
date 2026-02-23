// Declares the program's functionality

#include <stdio.h>
#include <string.h>

#include "structs.h"

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

// Add new entry
int add_new (study_log *logs_arr,int *arr_size, int *free_space) {
    char buffer[1024];
    int input_return;

    // Find the first empty index at the end of the array

    int arr_tail = (sizeof (*logs_arr) / sizeof (logs_arr[0])) - *free_space;

    printf ("Enter the Subject:\n");
    input_return = string_input (buffer, sizeof (buffer));

    if (input_return == 2) {
        strcpy (logs_arr->subject, "");
    } else {
        strcpy (logs_arr->subject, buffer);
    }
    return 0;
}
