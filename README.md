# Simple Shell

This is a simple shell implementation in C. The shell supports basic command execution, parsing, and checks for command accessibility in specified paths.

### Features

- Command Execution: Executes commands with or without specified paths.
- Command Parsing: Parses user input into command tokens.
- Path Checking: Checks for command accessibility in specified paths.
- Signal Handling: Handles the SIGINT signal (Ctrl + C) to exit the shell gracefully.

### Usage

#### Compile the Shell:

```
bash

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

#### Run the Shell:

```
bash

./hsh
```

#### Available Commands:

- Basic shell commands.
- Custom commands specified in the paths: "/usr/local/bin/", "/usr/bin/", "/bin/", "/usr/local/games/", "/usr/games/".

#### Exit the Shell:

```
bash

exit
```

### Function Descriptions

- main: Main function of the shell, responsible for handling user input and executing commands.
- check_access: Checks if a command has execute permission and searches for it in specified paths.
- execute_command: Executes the given command with arguments.
- parse_command: Parses the command into tokens.
- display_prompt: Displays the shell prompt.
- get_command: Reads a line of input from the user.
- sigintHandler: Signal handler for SIGINT (Ctrl + C).
