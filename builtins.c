#include "shell.h"

/**
 * print_environment - Prints the current environment
 */

void print_environment(void)
{
	char **env = environ;   /*environ - points to the env variables*/

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}

/**
 * execute_command - Executes a command with arguments
 * @args: Array of command and arguments
 * Return: 1 if shell should continue, 0 if should exit
 */

int execute_command(char **args)
{
	char *full_path;
	pid_t pid;
	int status;

	if (strcmp(args[0], "exit") == 0) /*Handle exit builtin*/
		return (0);

	if (strcmp(args[0], "env") == 0) /*Handle env builtin*/
	{
		print_environment();
		return (1);
	}

	full_path = find_in_path(args[0]); /*find command in PATH*/
	if (!full_path)
	{
		fprintf(stderr, "%s: command not found\n", args[0]);
		return (1);
	}

	pid = fork(); /*fork a child process*/
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		if (execve(full_path, args, environ) == -1) /*child process*/
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
		waitpid(pid, &status, 0); /*parent process*/

	free(full_path);
	return (1);
}

