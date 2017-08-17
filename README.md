# shell-v2
Shell Version 2

The project concepts are in

* https://github.com/SravanthiSinha/EYNTK-SHELL/blob/master/EYNTK-Shell-v1/README.md

* https://github.com/SravanthiSinha/EYNTK-SHELL/blob/master/EYNTK-Shell-v2/README.md

## hsh 1.0

A UNIX command line interpreter.

```
Usage: hsh
```

* Displays a prompt and wait for the user to type a command. A command line always ends with a new line.
* The prompt is displayed again each time a command has been executed.
* If an executable cannot be found, prints an error message and display the prompt again.
* Handle errors.
* Handles the "end of file" condition (Ctrl+D)
* Handles command lines with arguments
* Handles and parse the PATH environment variable

#### Builtins

Implemented the built-in command exit:

* exit built-in  behaves exactly like sh's
* Handles arguments

Implemented the built-in command cd:

* Changes the current directory of the process.
* Command syntax: cd [path]
* If no argument is given to cd the command is interpreted like cd $HOME
* Handles the command cd -

Implemented the built-in command env:

* Prints the current environment
