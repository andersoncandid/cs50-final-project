// Declares the program's functionality

#ifndef FUNCTIONALITY_C
#define FUNCTIONALITY_C

#include <stddef.h>

#include "definitions.h"

int string_input (char *buffer, size_t buffer_size);
void sort_arr (study_log *logs_arr, size_t arr_size, const char *log_key);
int search_arr (study_log *buffer_arr, study_log *logs_arr, size_t arr_size,
               const char *log_key, char *search_key);
int add_new (study_log **logs_arr, size_t *arr_size, size_t *free_space,
             char *last_ID);

#endif
