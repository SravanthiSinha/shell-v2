#include "builtins.h"

/**
 * hsh_unsetenv - un sets the Environmental varible
 * @shell : shell info
 * @args: This has the command "env"
 *
 * Return: On Success - HSH_SUCCESS, On Failure - 2
 */
int hsh_unsetenv(Shell *shell, char **args)
{
	int count = array_size(args);

	if (count > 1)
		_unsetenv(args[1]);
	else
	{
		print_error(shell, args[0], NULL, HSH_MISSING_ARGUMENTS);
		return (2);
	}
	return (HSH_SUCCESS);
}
