#include "builtins.h"

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
 * get_op_func - returns the function pointer of the corresponding builtin
 * @name: The builtin
 * Return: on success: valid function pointer - 0 , on Failure: NULL.
 */
int (*get_op_func(char *name))(Shell *, char **)
{
	int i;
	char *builtins[] = {"env", "cd"};
	funcPtr p[2] = {printenv, change_dir};

	for (i = 0; i < 2; i++)
		if (_strcmp(builtins[i], name) == 0)
			return (*p[i]);
	return (NULL);
}

/**
 * handle_builtins - Execute the builtins
 * @cmd: The builtin
 * @shell : shell info
 * Return: On Success - HSH_SUCCESS, On Failure - HSH_FAILURE.
 */
int handle_builtins(Shell *shell, Command *cmd)
{
	int count = 0;
	int (*a)(Shell *, char **);

	if (_strcmp(cmd->args[0], "exit") == 0)
	{
		count = array_size(cmd->args);
		if (count == 1)
			do_exit(shell, shell->exit_status);
		else if (count >= 2 && isNumericChar(cmd->args[1][0]))
			do_exit(shell, _atoi(cmd->args[1]));
		else
			print_error(shell, "exit", cmd->args[1], HSH_ILLEGAL_NUMBER);
		return (2);
	}
	a = get_op_func(cmd->args[0]);
	if (a == NULL)
	{
		print_error(shell, cmd->args[0], NULL, HSH_COMMAND_NOT_FOUND);
		return (HSH_FAILURE);
	}
	return ((*a)(shell, cmd->args));
}
