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
		if (_strcmp(builtins[i], name) == 0)
			return (1);
	return (0);
}

/**
 * validate_command - Validates if the command/path can exsits
 * @shell : shell info
 * @cmd: command to be validated
 * Return: On Success - HSH_SUCCESS, On Failure - HSH_FAILURE.
 */
int validate_command(Shell *shell, Command *cmd)
{
	if (cmd->args && cmd->args[0])
	{
		if (is_builtin(cmd->args[0]))
			return (HSH_SUCCESS);
		else if (cmd->path == NULL)
		{
			print_error(shell, cmd->args[0], NULL, HSH_COMMAND_NOT_FOUND);
			return (127);
		}
		else if (cmd->path)
		{
			if (!exe_exists(cmd->path))
			{
				print_error(shell, NULL, cmd->path, HSH_NO_FILE_DIR);
				return (HSH_FAILURE);
			}
		}
	}
	return (HSH_SUCCESS);
}
