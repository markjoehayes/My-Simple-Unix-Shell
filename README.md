# Simple Shell Project

## Description

This is a simple UNIX command line interpreter (shell) written in C. The shell supports basic command execution, PATH handling, and includes built-in commands like `exit` and `env`.

## Features

- **Command Execution**: Executes commands with arguments
- **PATH Handling**: Searches for commands in PATH directories
- **Built-in Commands**:
  - `exit`: Terminates the shell
  - `env`: Prints the current environment variables
- **Error Handling**: Reports command not found errors
- **Interactive Mode**: Displays a prompt (`$ `) when input is from a terminal
- **Non-interactive Mode**: Supports command execution from scripts/pipes

## Requirements

- GCC compiler
- GNU Make (optional)
- Linux/Unix environment

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/simple_shell.git
   cd simple_shell
   ```

2. Compile the shell:
   ```bash
   gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
   ```

## Usage

### Interactive Mode
Run the shell and enter commands:
```bash
$ ./hsh
$ ls -l
$ echo "Hello World"
$ env
$ exit
```

### Non-interactive Mode
Pipe commands to the shell:
```bash
echo "ls -l" | ./hsh
```

## Examples

```bash
$ ./hsh
$ /bin/ls
file1.txt  file2.txt  hsh  README.md
$ env
USER=john
HOME=/home/john
PATH=/usr/local/bin:/usr/bin:/bin
$ exit
```

## File Structure

- `main.c` - Main shell implementation
- `builtins.c` - Built-in command handlers
- `helpers.c` - Helper functions (PATH resolution, etc.)
- `shell.h` - Header file with function prototypes
- `README.md` - This documentation file
- `AUTHORS` - List of contributors

## Built-in Commands

| Command | Description |
|---------|-------------|
| `exit`  | Exits the shell |
| `env`   | Prints all environment variables |

## Limitations

- Does not support advanced shell features like pipes, redirections, or wildcards
- No support for shell scripting (if/else, loops, etc.)
- Simple error handling

## Bugs

No known bugs at this time. Please report any issues found.

## Authors

- Mark Hayes(https://github.com/markjoehayes)


