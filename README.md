# Simple Shell

## Description
This project is a simple UNIX command line interpreter written in C.  
It mimics basic behavior of the standard shell and executes commands entered by the user.

The shell reads input from standard input or from a file, parses commands, searches for executable files using the PATH environment variable, and executes them using system calls.

---

## Features
- Displays a prompt in interactive mode
- Executes commands with arguments
- Searches commands using the PATH variable
- Supports absolute and relative paths
- Handles commands when PATH is missing by using a default path
- Executes commands from a file
- Implements a basic `exit` command

---

## Files Description
| File           | Description |
|----------------|-------------|
| `shell.c`    | Contains the main function of the shell. Handles the main loop, reads input, parses commands, and executes them. |
| `shell_headers.h`  | Header file that contains all function prototypes and required system headers. |
| `parsing_functions.c`| Handles input parsing: trimming spaces, tokenizing commands, and determining input source (stdin or file). |
| `path_functions.c` | Searches for executable command paths using the PATH environment variable and a default fallback path. |
| `execute_functions.c` | Handles process creation using `fork`, executes commands with `execve`, and returns exit status. |
| `env_functions.c` | Retrieves environment variables, specifically the *PATH* variable. |
| `io_functions.c` | Handles shell input/output: displaying the prompt and cleaning allocated resources. |
---

## Compilation
Use the following command to compile the shell:

```bash
gcc -Wall -Werror -Wextra -pedantic *.c -o shell
```

## Usage

### Interactive mode
```bash
./hsh
```

Example:
```bash
cisfun$ ls
cisfun$ pwd
```

### Non-interactive mode
```bash
echo "ls -l" | ./hsh
```

### File input
```bash
./hsh commands.txt
```

---
## Environment Handling
- If the PATH variable exists, the shell uses it to locate commands
- If PATH is not set, the shell falls back to:
```bash
/bin:/usr/bin
```
This ensures standard commands like `env` continue to work.

---

## Exit status
- Returns `0` on successful execution
- Returns `127` when a command is not found

---
## Authors

Badr Alshaya, Haitham ALshehri
