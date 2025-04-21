#include "shell.h"

/**
 * print_environment - Prints the current environment
 */

void print_environment(void)
{
    char **env = environ;   /*environ - points to the env variables*/
    while (*env) {
        printf("%s\n", *env);
        env++;
    }
}

/**
 * execute_command - Executes a command with arguments
 * @args: Array of command and arguments
 *
 * Return: 1 if shell should continue, 0 if should exit
 */

int execute_command(char **args)
{
    char *full_path;
    pid_t pid;
    int status;

    /* Handle exit built-in */
    if (strcmp(args[0], "exit") == 0) {
        return 0;
    }

    /* Handle env built-in */
    if (strcmp(args[0], "env") == 0) {
        print_environment();
        return 1;
    }

    /* Find command in PATH */
    full_path = find_in_path(args[0]);
    if (!full_path) {
        fprintf(stderr, "%s: command not found\n", args[0]);
        return 1;
    }

    /* Fork a child process */
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        /* Child process */
        if (execve(full_path, args, environ) == -1) {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    } else {
		/* Parent process */
        waitpid(pid, &status, 0);
    }

    free(full_path);
    return 1;
}

