#include "shell.h"

/**
 * split_line - Splits a command line into arguments
 * @line: The command line to split
 *
 * Return: Array of arguments (must be freed by caller)
 */

char **split_line(char *line)
{
	/*initialize buffer and allocate memory for an array of strings*/
    int bufsize = MAX_ARGS, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens) {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }
	/*tokanize (break a line of tokens from delimiters)*/
    token = strtok(line, " \t\r\n\a");
    while (token != NULL) {
        tokens[position] = token;
        position++;
		
		/*resize if necessary*/
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
	/*terminate with NULL as required by execvp() style functions*/
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


