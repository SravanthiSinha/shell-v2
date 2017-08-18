#ifndef _BUILTINS_H_
#define _BUILTINS_H_

#include "hsh.h"

typedef int (*funcPtr)(Shell *shell, char **);
void do_exit(Shell *shell, int exit_status);
int printenv(Shell *shell, char **args);
int change_dir(Shell *shell, char **args);
#endif
