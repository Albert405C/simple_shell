#include "shell.h"

/**
 * main - Entry point for the shell program
 * @argc: Number of command-line arguments
 * @argv: Array of command-line argument strings
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int main(int argc, char **argv)
{
    info_t info = INFO_INIT;
    int fd;

    if (argc == 2)
    {
        fd = open(argv[1], O_RDONLY);
        if (fd == -1)
        {
            perror(argv[0]);
            exit(EXIT_FAILURE);
        }
        info.readfd = fd;
    }

    populate_env_list(&info);
    read_history(&info);
    hsh(&info, argv);

    return EXIT_SUCCESS;
}

