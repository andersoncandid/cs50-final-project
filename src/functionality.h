// Declares the program's functionality

#ifndef FUNCTIONALITY_C
#define FUNCTIONALITY_C

#include <stddef.h>

#include "definitions.h"

int string_input (char *buffer, const size_t buffer_size);
void sort_arr (study_log *array, const size_t arr_size, const char *sort_value);
int search_arr (study_log *results_arr, study_log *logs_arr, const size_t arr_size,
               const char *search_member, const char *search_value);
int add_new (study_log **logs_arr, size_t *arr_size, size_t *free_space,
             char *last_ID);
int search_ID (const study_log *logs_arr, const size_t arr_size,
               const char *target_ID);
int edit_log (study_log *logs_arr, const size_t arr_size, const int target_index);

#endif
