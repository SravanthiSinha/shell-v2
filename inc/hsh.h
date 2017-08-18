#ifndef _HSH_H_
#define _HSH_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "signals.h"
#include "strings.h"
#include "command.h"
#include "utils.h"

#define HSH_NOT_FOUND 0
#define HSH_TOO_MANY_ARGS 1
#define HSH_NO_FILE_DIR 2
#define HSH_IS_DIR 3
#define HSH_IS_NOT_DIR 4

extern char **environ;

/**
 * struct Shell - Shell
 * @isatty: defines if its a tty
 * @stdin_fd: file descriptor of a stdin
 * @cmdLine: user input
 * @exit_code: exit code of previous command
 * @cmds:  list of commands
 * @home: $HOME environmental variable
 * @pwd: $PWD environmental variable
 * @oldpwd: $OLDPWD environmental variable
 */
typedef struct Shell
{
	int isatty;
	int stdin_fd;
	char *cmdLine;
	int exit_code;
	Command *cmds;
	char *home;
	char *pwd;
	char *oldpwd;
} Shell;

void init_shell(Shell *shell);
void terminate_shell(Shell *shell);

void printPrompt(Shell *shell);

char *readCommandLine(Shell *shell);

Command *parseCommand(char *input, int *exit_status);

void get_exes(Shell *shell);
void print_error(char *cmd, char *path,  int error);
int validate_commands(Command *cmds);
int command_exec(Shell *shell);
int execute_builtin(char *name);
int exe_exists(char *s);
#endif
