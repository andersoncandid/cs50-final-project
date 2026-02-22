#include <stdio.h>
#include <string.h>


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

//   if (string_input(nome, sizeof(nome)) == 2) {
//   struct.key = ""; // Em caso de entrada vazia uma string vazia é
//   adicionada
//                    // ao registro
// }
