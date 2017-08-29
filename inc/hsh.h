#ifndef _HSH_H_
#define _HSH_H_

#include "command.h"
#include "signals.h"
#include "strings.h"
#include "utils.h"
#include <fcntl.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define HSH_SUCCESS 0
#define HSH_FAILURE 1
#define HSH_COMMAND_NOT_FOUND 2
#define HSH_TOO_MANY_ARGS 3
#define HSH_NO_FILE_DIR 4
#define HSH_IS_DIR 5
#define HSH_IS_NOT_DIR 6
#define HSH_SYNTAX_ERROR 7

#define HSH_OP_NONE 0
#define HSH_OP_AND 1
#define HSH_OP_OR 2
#define HSH_OP_ROOT 3
#define HSH_OP_PIPE 4
#define HSH_OP_REDIRECT_OUT_CONCAT 5
#define HSH_OP_REDIRECT_OUT 6
#define HSH_OP_REDIRECT_IN_HEREDOC 7
#define HSH_OP_REDIRECT_IN 8
#define HSH_OP_REDIRECT_PIPE_OUT 9
#define HSH_OP_REDIRECT_PIPE_IN 10

#define READ_END 0
#define WRITE_END 1

extern char **environ;

/**
 * struct Shell - Shell
 * @isatty: defines if its a tty
 * @std: file descriptor to be stored for stdin, stdout, stderr
 * @pipefd: pipefd
 * @cmdLine: user input
 * @exit_status: exit code of previous command
 * @cmds:  list of commands
 * @home: $HOME environmental variable
 * @program : name of the program
 * @pwd: $PWD environmental variable
 * @oldpwd: $OLDPWD environmental variable
 */
typedef struct Shell
{
	int isatty;
	char *cmdLine;
	int exit_status;
	struct Command **cmds;
	int std[3];    /* for redirection of stdin, stdout, stderr*/
	int pipefd[2]; /* for redirection when pipe is used*/
	char *home;
	char *pwd;
	char *program;
	char *oldpwd;
} Shell;

/**
 * struct token_s - token_s
 * @token : token
 * @len : length of the token
 * @id : token id
 */
typedef struct token_s
{
	char *token;
	int len;
	int id;
} token_t;


void init_shell(Shell *shell);
void terminate_shell(Shell *shell);

void printPrompt(Shell *shell);

char *readCommandLine(Shell *shell);

void get_exes(Shell *shell);

void lexer_run(Shell *shell, Command **cmds);

void exec_commands(Shell *shell);

int handle_redirections(Shell *shell, Command *cmd);

int is_builtin(char *name);

int validate_command(Shell *shell, Command *cmd);

void print_error(Shell *shell, char *cmd, char *path, int error_code);

int handle_builtins(Shell *shell, Command *cmd);

int execute_builtin(char *name);


void do_exit(Shell *shell, int exit_status);
#endif
