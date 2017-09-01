#include "builtins.h"

/**
 * hsh_setenv - sets the Environmental varible
 * @shell : shell info
 * @args: This has the command "env"
 *
 * Return: On Success - HSH_SUCCESS, On Failure - 2
 */
int hsh_setenv(Shell *shell, char **args)
{
	int count = array_size(args);

	if (count > 2)
		_setenv(args[1], args[2], 1);
	else
	{
		print_error(shell, args[0], NULL, HSH_MISSING_ARGUMENTS);
		return (2);
	}
	return (HSH_SUCCESS);
}
