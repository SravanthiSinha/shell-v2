#include "hsh.h"

/**
 * print_error - Prints the the error message.
 * @shell : shell info
 * @cmd:  command string
 * @path:  path of the command
 * @error_code: error_code
 * Return: void
 */
void print_error(Shell *shell, char *cmd, char *path, int error_code)
{
	if (error_code == HSH_COMMAND_NOT_FOUND && !shell->isatty)
		printf("%s: 1: %s: command not found\n", shell->program, cmd);
	else if (error_code == HSH_COMMAND_NOT_FOUND)
		printf("%s: command not found\n", cmd);
	else if (error_code == HSH_TOO_MANY_ARGS)
		printf("%s\n%s: %s: too many arguments\n", cmd, shell->program, cmd);
	else if (error_code == HSH_NO_FILE_DIR)
	{
		if (cmd != NULL)
			printf("%s: %s: %s: No such file or directory\n", shell->program, cmd,
			       path);
		else
			printf("%s: %s: No such file or directory\n", shell->program, path);
	}
	else if (error_code == HSH_IS_DIR)
		printf("%s: %s: Is a directory\n", shell->program, path);
	else if (error_code == HSH_IS_NOT_DIR)
		printf("%s: %s: Not a directory\n", shell->program, path);
	else if (error_code == HSH_SYNTAX_ERROR)
		printf("%s: syntax error near unexpected token `%s'\n", shell->program,
		       cmd);
	if (!shell->isatty && error_code == HSH_SYNTAX_ERROR)
		do_exit(shell, 2);
	if (error_code == HSH_COMMAND_NOT_FOUND)
		shell->exit_status = 127;
	else
		shell->exit_status = HSH_FAILURE;
}
