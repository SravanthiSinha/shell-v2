#include "builtins.h"

/**
 * printenv - Prints the Environmental varibles
 * @shell : shell info
 * @args: This has the command "env"
 *
 * Return: On Success - HSH_SUCCESS, On Failure - HSH_FAILURE
 */
int printenv(Shell *shell, char **args)
{
	int count = 0;
	int i = 0;

	count = array_size(args);
	if (count == 1)
	{
		shell->exit_status = HSH_SUCCESS;
		while (*environ && environ[i])
		{
			printf("%s\n", environ[i]);
			i++;
		}
	}
	else if (count > 1)
	{
		print_error(shell, args[0], args[1], HSH_NO_FILE_DIR);
		return (2);
	}
	return (HSH_SUCCESS);
}
