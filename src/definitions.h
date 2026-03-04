// Define the program's structs and constants

#ifndef STRUCTS_H
#define STRUCTS_H

#define ENTRY_LENGTH 128
#define DATE_LENGTH 20
#define FREE_SPACE 100 // Empty space on end of logs_arr
#define MAX_RESULTS 50 // Max results found on searches

// Defining the output colors
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define RESET   "\033[0m"

typedef enum {
    ID,
    subject,
    topic,
    start_date,
    end_date,
} log_key;
typedef int (*comp_func) (const void *a, const void *b);

// Study record structure
typedef struct {
    char ID[DATE_LENGTH];
    char subject[ENTRY_LENGTH];
    char topic[ENTRY_LENGTH];
    char start_date[DATE_LENGTH]; // AAAA-MM-DD
    char end_date[DATE_LENGTH];
    char status[ENTRY_LENGTH];
} study_log;

#endif
