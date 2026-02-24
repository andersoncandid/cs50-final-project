// Declares the program's functionality

#ifndef FUNCTIONALITY_C
#define FUNCTIONALITY_C

#include <stddef.h>

#include "definitions.h"

int string_input (char *buffer, size_t buffer_size);
int add_new (study_log *logs_arr, int *arr_size, int *free_space);
int id_cmp (const void *a, const void *b);
int subj_cmp (const void *a, const void *b);
int top_cmp (const void *a, const void *b);
int start_cmp (const void *a, const void *b);
int end_cmp (const void *a, const void *b);

#endif
