// Define the program's structs and constants

#ifndef STRUCTS_H
#define STRUCTS_H

#define ENTRY_LENGTH 128
#define DATE_LENGTH 20
#define FREE_SPACE 100 // Empty space on logs_arr tail

typedef enum { IN_PROGRESS, FINISHED, REMOVED } study_status;
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
    study_status status;
} study_log;

#endif
