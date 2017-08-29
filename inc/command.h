#ifndef _COMMAND_H_
#define _COMMAND_H_


#define MAX_COMMANDS 1024

/**
 * struct Command - Command with path, args & oprators
 * @args : command arguments for the command to be execute_cmd
 * @path: path of the command if one Exits
 * @redirect_type: type of the redirection
 * @redirect_to: redirect to
 * @op: operation to be carried on
 * @next : A pointer to the next node of the Command
 */
typedef struct Command
{
	char *path;
	char **args;
	int	redirect_type;
	char *redirect_to;
	int	op;
	struct Command *next;
} Command;

#define FREE(x) free(x);\
	x = NULL

int command_size(Command *command);
void command_init(Command **command);
void print_commands(Command *command);
void free_commands(Command *head);
#endif
