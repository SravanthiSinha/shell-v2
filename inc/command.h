#ifndef _COMMAND_H_
#define _COMMAND_H_

/**
 * struct Command - Command with path, options, builtin or nor
 * @str : cmd to be executed
 * @args : command arguments for the command to be execute_cmd
 * @path: path of the command if one Exits
 * @builtin: Specifies if the comman id a builtin
 * @next : A pointer to the next node of the Command
 */
typedef struct Command
{
	char *str;
	char **args;
	char *path;
	int builtin;
	struct Command *next;
} Command;

int command_size(Command *command);
int command_add(Command **command, char *str, char *args);
void print_command(Command *command);
void free_command(Command *head);
#endif
