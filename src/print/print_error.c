#include "hsh.h"


/**
 * print_error - Prints the the error message.
 * @cmd:  command string
 * @path:  path of the command
 * @error_code: error_code
 * Return: void
 */
void print_error(char *cmd, char *path, int error_code)
{
	if (error_code == HSH_NOT_FOUND)
		printf("%s: command not found\n", cmd);
	else if (error_code == HSH_TOO_MANY_ARGS)
		printf("%s\nhsh: %s: too many arguments\n", cmd, cmd);
	else if (error_code == HSH_NO_FILE_DIR)
	{
		if (cmd != NULL)
			printf("hsh: %s: %s: No such file or directory\n", cmd, path);
		else
			printf("hsh: %s: No such file or directory\n", path);
	}
	else if (error_code == HSH_IS_DIR)
		printf("hsh: %s: Is a directory\n", path);
	else if (error_code == HSH_IS_NOT_DIR)
		printf("hsh: %s: Not a directory\n", path);
}
