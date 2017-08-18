#include "hsh.h"
/**
 * get_op_func - returns the function pointer of the corresponding builtin
 * @name: The builtin
 * Return: on success: valid function pointer - 0 , on Failure: NULL.
 */
int (*get_op_func(char *name))(char **)
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
 * executeBuiltInCommand - Execute the builtins
 * @shell : shell info
 * Return: On Success - EXIT_SUCCESS, On Failure - EXIT_FAILURE.
 */
int executeBuiltInCommand(Shell *shell)
{
	int count = 0;
	int (*a)(char **);

	if (_strcmp(cmd->str, "exit") == 0)
	{
		count = array_size(cmd->args);
		if (count == 1)
			do_exit(input, cmd, *prev_status);
		if (count > 2 && are_numbers(cmd->args + 1))
		{
			print_error(cmd->str, NULL, HSH_TOO_MANY_ARGS);
			*prev_status = 1;
			return (EXIT_FAILURE);
		}
		else
			do_exit(input, cmd, _atoi(cmd->args[1]));
	}
	a = get_op_func(cmd->str);
	if (a == NULL)
	{
		print_error(cmd->str, NULL, HSH_NOT_FOUND);
		*prev_status = 1;
		return (EXIT_FAILURE);
	}
	return ((*a)(cmd->args));
}


/**
 * isBuiltInCommand - Validates if the name is a builtin
 * @name: The builtin to be validated.
 * Return: On Success - 1, On Failure - 0.
 */
int isBuiltInCommand(char *name)
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
