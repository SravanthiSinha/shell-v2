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
	char *error_msg = NULL;
	FILE *op = stdout;

	if (!shell->isatty)
		op = stderr;
	if (error_code == HSH_COMMAND_NOT_FOUND)
		error_msg = _strdup("not found");
	else if (error_code == HSH_ILLEGAL_NUMBER)
		error_msg = _strdup("Illegal number:");
	else if (error_code == HSH_NO_FILE_DIR)
		error_msg = _strdup("No such file or directory");
	else if (error_code == HSH_CANNOT)
		error_msg = _strdup("can't cd to");
	else if (error_code == HSH_SYNTAX_ERROR)
		error_msg = _strdup("Syntax error");
	if (!shell->isatty && error_code == HSH_SYNTAX_ERROR)
		do_exit(shell, 2);
	if (error_code == HSH_COMMAND_NOT_FOUND)
		shell->exit_status = 127;
	else
		shell->exit_status = HSH_FAILURE;
	if (path)
		fprintf(op, "%s: %d: %s: %s %s\n", shell->program, shell->lineno, cmd,
			error_msg, path);
	else
		fprintf(op, "%s: %d: %s: %s\n", shell->program, shell->lineno, cmd,
			error_msg);
	free(error_msg);
	fflush(stderr);
}
