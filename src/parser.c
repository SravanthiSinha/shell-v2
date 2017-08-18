#include "hsh.h"

/**
 * parseCommand - created the Command based on user input
 * @input: pointer to the user input.
 * @exit_code: exit code
 * Return: parsed input into command
 */
Command *parseCommand(char *input, int *exit_code)
{
	char **arr = NULL;
	Command *cmds = NULL;

	arr = _stringsplit(input, ' ', 0);
	command_add(&cmds, arr[0], input, exit_code);
	free_array(arr);
	return (cmds);
}
