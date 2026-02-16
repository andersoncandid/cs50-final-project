#include <stdio.h>
#include <string.h>

int safe_string_input (char *buffer, size_t buffer_size) {
    if (fgets (buffer, buffer_size, stdin) == NULL) {
        return 0; // Input error
    }

    // Remove trailing newline
    buffer[strcspn (buffer, "\n")] = 0;

    // Check for empty input
    if (strlen (buffer) == 0) {
        return 0;
    }

    // Check if the input exceeds the size
    if (strchr (buffer, '\n') == NULL) {

        // Clean stdin
        int c;
        while ((c = getchar ()) != '\n')
            ;
    }

    return 1;
}

    //   if (safe_string_input(nome, sizeof(nome)) == 0) {
    //   struct.key = ""; // Em caso de erro na entrada uma string vazia é
    //   adicionada
    //                    // ao registro
    // }
