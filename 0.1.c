#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char *input;

    while (1) {
        printf("#cisfun$ ");
        getline(&input, NULL, stdin);
        // Process the input
        // Implement the execution of the command
    }

    free(input);
    return 0;
}

