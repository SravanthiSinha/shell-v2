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
#include "builtins.h"
#include "utils.h"

#define HSH_NOT_FOUND 0
#define HSH_TOO_MANY_ARGS 1
#define HSH_NO_FILE_DIR 2
#define HSH_IS_DIR 3
#define HSH_IS_NOT_DIR 4

extern char **environ;
char *prompt_user(void);
int get_commands(char *input, Command **cmds);
void get_exes(Command *cmds);
char *_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
int exe_exists(char *s);
void print_error(char *cmd, char *path,  int error);
int validate_commands(Command *cmds);
int execute_cmd(Command *cmds, int *prev_status);
int execute_builtin(char *name);
int exe_exists(char *s);
#endif
