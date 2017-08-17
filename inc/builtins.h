#ifndef _BUILTINS_H_
#define _BUILTINS_H_


typedef int (*funcPtr)(char **);
void do_exit(int exit_status);
int printenv(char **args);
int change_dir(char **args);
#endif
