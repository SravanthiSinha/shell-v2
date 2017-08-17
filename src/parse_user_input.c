#include "hsh.h"

/**
 * get_commands - created the Command based on user input
 * @input: pointer to the user input.
 * @cmds: The list of commands to be executed
 * Return: On Success - EXIT_SUCCESS, On Failure - EXIT_FAILURE.
 */
int get_commands(char *input, Command **cmds)
{
	char **arr = NULL;
	int count = 0, exit_status = EXIT_SUCCESS;

	arr = _stringsplit(input, ' ', &count);
	exit_status = command_add(cmds, arr[0], input);
	free_array(arr);
	return (exit_status);
}
