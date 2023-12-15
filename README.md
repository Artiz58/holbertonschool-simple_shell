# Simple Shell

Welcome to the Simple Shell! This document provides an overview of the code's functionality and usage.

### Overview

This code implements a basic shell program capable of taking user input, parsing commands, and executing them. It allows users to:

- Run commands: Enter commands directly or from a file.
- Access files: Execute applications and scripts located in various directories.
- Navigate directories: Use built-in commands like ```cd``` to change directories.
- Exit the shell: Use the ```exit``` command to terminate the program.

### Key Functions

The code relies on several key functions to achieve its functionality:

- error: Handles and displays error messages when a command is not found.
- main: Drives the main loop of the shell, taking user input, parsing commands, and executing them.
- get_tokens: Takes a user input string and parses it into an array of tokens (arguments).
- get_path: Searches for the executable file associated with a command in various predefined paths.
- my_exe: Creates a child process to execute the command using ```execve```.
- white_spaces: Checks if the user input contains only whitespace characters.
- free_array: Frees the memory allocated for the token array.
- remove_newline: Removes the newline character from the user input string.
### Usage

To run the shell, compile the code and execute the resulting binary. You can then enter commands directly in the terminal. For example:

```
./hsh
($) ls
($) cat file.txt
($) cd /home/user
($) pwd
($) exit
```

### Additional Notes

- The shell currently supports basic built-in commands like exit and ```cd```.
- The shell can execute commands located in various predefined paths, including ```/usr/bin``` and ```/usr/local/bin```.
- The code includes safety measures to handle errors and prevent potential vulnerabilities.

### Further Development

This is a basic shell implementation, and it can be further extended with additional features such as:

- More built-in commands for file manipulation, process control, etc.
- Support for environment variables.
- Command history and auto-completion.
- Scripting capabilities.

We encourage you to explore the code and contribute to its development!
