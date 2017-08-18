#include "builtins.h"

/**
 * printenv - Prints the Environmental varibles
 * @shell : shell info
 * @args: This has the command "env"
 *
 * Return: On Success - EXIT_SUCCESS, On Failure - EXIT_FAILURE
 */
int printenv(Shell __attribute__((unused)) * shell, char **args)
{
	int count = 0;
	int i = 0;

	count = array_size(args);
	if (count == 1)
	{
		while (environ && environ[i])
		{
			printf("%s\n", environ[i]);
			i++;
		}
	}
	if (!args)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
