// Declares the program's functionality

#ifndef FUNCTIONALITY_C
#define FUNCTIONALITY_C

#include <stddef.h>

#include "definitions.h"

int string_input (char *buffer, size_t buffer_size);
int id_cmp (const void *a, const void *b);
int subj_cmp (const void *a, const void *b);
int top_cmp (const void *a, const void *b);
int start_cmp (const void *a, const void *b);
int end_cmp (const void *a, const void *b);
study_log *arr_search (study_log *logs_arr, size_t *arr_size, const char *log_key, char *search_key);
int add_new (study_log *logs_arr, size_t *arr_size, size_t *free_space);

#endif
