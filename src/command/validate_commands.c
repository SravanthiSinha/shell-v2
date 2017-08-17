#include "hsh.h"

/**
 * is_builtin - Validates if the name is a builtin
 * @name: The builtin to be validated.
 * Return: On Success - 1, On Failure - 0.
 */
int is_builtin(char *name)
{
	char *builtins[] = {"exit", "env", "cd"};
	int i = 0;

	for (i = 0; i < 3; i++)
	{
		if (_strcmp(builtins[i], name) == 0)
			return (1);
	}
	return (0);
}

/**
 * validate_commands - Validates if the command/path can exsits
 * @cmds: The list of commands to be executed
 * Return: On Success - EXIT_SUCCESS, On Failure - EXIT_FAILURE.
 */
int validate_commands(Command *cmds)
{
	Command *cmd;

	cmd = cmds;
	while (cmd)
	{
		if (cmd->str)
		{
			if (is_builtin(cmd->str))
			{
				cmd->builtin = 1;
			}
			else if (cmd->path == NULL)
			{
				print_error(cmd->str, NULL, HSH_NOT_FOUND);
				return (EXIT_FAILURE);
			}
		}
		else if (cmd->path && cmd->str == NULL)
		{
			if (!exe_exists(cmd->path))
			{
				print_error(NULL, cmd->path, HSH_NO_FILE_DIR);
				return (EXIT_FAILURE);
			}
		}
		cmd = cmd->next;
	}
	return (EXIT_SUCCESS);
}
