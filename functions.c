#include "shell.h"


/**
 * split_line - Splits a command line into arguments
 * @line: The command line to split
 * 
 * Return: Array of arguments (must be freed by caller)
 */
char **split_line(char *line)
{
    int bufsize = MAX_ARGS, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens) {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " \t\r\n\a");
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += MAX_ARGS;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[position] = NULL;
    return tokens;
}

/**
 * find_in_path - Finds the full path of a command
 * @command: The command to find
 * 
 * Return: Full path if found, NULL otherwise
 */

char *find_in_path(char *command)
{
    char *path_env, *path_copy, *dir, *full_path;
    struct stat st;

    /* Check if command contains '/' (already a path) */
    if (strchr(command, '/') != NULL) {
        if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR))
            return strdup(command);
        return NULL;
    }

    /* Get PATH environment variable */
    path_env = getenv("PATH");
    if (!path_env)
        return NULL;

    path_copy = strdup(path_env);
    if (!path_copy)
        return NULL;

    dir = strtok(path_copy, ":");
    while (dir != NULL) {
        full_path = malloc(strlen(dir) + strlen(command) + 2);
        if (!full_path) {
            free(path_copy);
            return NULL;
        }

        sprintf(full_path, "%s/%s", dir, command);
        if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR)) {
            free(path_copy);
            return full_path;
        }

        free(full_path);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}

/**
 * print_environment - Prints the current environment
 */
void print_environment(void)
{
    char **env = environ;
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

