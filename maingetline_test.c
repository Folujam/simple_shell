#include "shell.h"
#define BUFFER_SIZE 10

// Assume you have implemented your getline function

int main() {
    char *line = NULL;
    size_t len = BUFFER_SIZE;

    printf("Enter a line of text (limit to %zu characters): ", BUFFER_SIZE - 1);
    ssize_t characters_read = getline(&line, &len, stdin);

    if (characters_read != -1) {
        printf("You entered: %s\n", line);
    } else {
        perror("getline");
    }

    free(line);

    return 0;
}
