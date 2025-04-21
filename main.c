#include "shell.h"

/**
 * main - Simple UNIX command line interpreter with exit and env built-ins
 *
 * Return: Always 0
 */

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char **args;
    int status;

    /* Interactive mode if input is from terminal */
    if (isatty(STDIN_FILENO))
        printf("$ ");

    while ((read = getline(&line, &len, stdin)) != -1)
    {
        /* Remove newline character */
        if (line[read - 1] == '\n')
            line[read - 1] = '\0';

        /* Skip empty lines */
        if (strlen(line) == 0)
        {
            if (isatty(STDIN_FILENO))
                printf("$ ");
            continue;
        }

        /* Split line into arguments */
        args = split_line(line);

        /* Execute command */
        status = execute_command(args);
        free(args);

        /* Check if we should exit */
        if (!status) {
            break;
        }

        if (isatty(STDIN_FILENO))
            printf("$ ");
   }
   /* Handle EOF (Ctrl+D) */
    if (isatty(STDIN_FILENO))
        printf("\n");

    free(line);
    exit(EXIT_SUCCESS);

}


