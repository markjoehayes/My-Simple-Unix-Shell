#ifndef SHELL_H
#define SHELL_H

/*header files*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stddef.h>
#include<sys/stat.h>  
#include<sys/types.h>
#include<sys/wait.h>

/*Global variable*/
extern char **environ;

/*Macros*/
#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64
#define MAX_PATH_LENGTH 4096


/*Function Headers*/
/**
  * split_line - Splits a command line into arguments
  * @line: The command line to split
  *
  * Return: Array of arguments (must be freed by caller)
  */

char **split_line(char *line);

/**
 * find_in_path - Finds the full path of a command
 * @command: The command to find
 *
 * Return: Full path if found, NULL otherwise
 */

char *find_in_path(char *command);

/**
 * print_environment - Prints the current environment
 */

void print_environment(void);

/**
 * execute_command - Executes a command with arguments
 * @args: Array of command and arguments
 * 
 * Return: 1 if shell should continue, 0 if should exit
 */

int execute_command(char **args);




#endif /* SHELL_H */
