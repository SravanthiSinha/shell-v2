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
		fprintf(stderr, "%s: 1: %s: not found\n", shell->program, cmd);
	else if (error_code == HSH_COMMAND_NOT_FOUND)
		fprintf(stderr, "%s: not found\n", cmd);
	else if (error_code == HSH_TOO_MANY_ARGS)
		fprintf(stderr, "%s\n%s: %s: too many arguments\n", cmd, shell->program,
			cmd);
	else if (error_code == HSH_NO_FILE_DIR)
	{
		if (cmd != NULL)
			fprintf(stderr, "%s: %s: %s: No such file or directory\n", shell->program,
				cmd, path);
		else
			fprintf(stderr, "%s: %s: No such file or directory\n", shell->program,
				path);
	}
	else if (error_code == HSH_IS_DIR)
		fprintf(stderr, "%s: %s: Is a directory\n", shell->program, path);
	else if (error_code == HSH_IS_NOT_DIR)
		fprintf(stderr, "%s: %s: Not a directory\n", shell->program, path);
	else if (error_code == HSH_SYNTAX_ERROR)
		fprintf(stderr, "%s: syntax error near unexpected token `%s'\n",
			shell->program, cmd);
	if (!shell->isatty && error_code == HSH_SYNTAX_ERROR)
		do_exit(shell, 2);
	if (error_code == HSH_COMMAND_NOT_FOUND)
		shell->exit_status = 127;
	else
		shell->exit_status = HSH_FAILURE;
}
