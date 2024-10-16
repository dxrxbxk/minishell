# Minishell

## usage: 
To build use `make` or `make bonus`

## features:
### builtins:
- **echo**: Displays a message or string in the terminal. Example: echo "Hello World" will print Hello World.
- **cd**: Changes the current directory. Example: cd /home/user will navigate to the home/user directory.
- **export**: Sets or modifies an environment variable to make it available to child processes. Example: export PATH=$PATH:/new/path adds a new path to the PATH environment variable.
- **unset**: Removes an environment variable or shell variable. Example: unset VAR_NAME will delete the environment variable VAR_NAME.
- **env**: Displays the current environment variables or can be used to run a command in a modified environment. Example: env will list all environment variables.
- **pwd**: Prints the current working directory (the directory you are currently in). Example: pwd will show the full path of the current directory.

### parser

### AST
