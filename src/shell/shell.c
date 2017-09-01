#include "hsh.h"

/**
 * init_shell - Intialialises the shell with enviroanmental variables and
 * others defaults
 * @shell : shell info
 * @argv: Input  to the program
 */
void init_shell(Shell *shell, char *argv[])
{
	shell->std[0] = -1;
	shell->std[1] = -1;
	shell->std[2] = -1;
	shell->isatty = isatty(STDIN_FILENO);
	shell->exit_status = HSH_SUCCESS;
	shell->cmdLine = NULL;
	shell->cmds = NULL;
	shell->lineno = 0;
	shell->program = _strdup(argv[0]);
	shell->home = _getenv("HOME");
}

/**
 * terminate_shell - frees the shell info.
 * others defaults
 * @shell : shell info
 */
void terminate_shell(Shell *shell)
{
	if (shell != NULL)
	{
		if (shell->cmdLine != NULL)
		{
			free(shell->cmdLine);
			shell->cmdLine = NULL;
		}
		if (shell->home != NULL)
		{
			free(shell->home);
			shell->home = NULL;
		}
		if (shell->program != NULL)
		{
			free(shell->program);
			shell->program = NULL;
		}
		if (shell->cmds != NULL)
		{
			free_commands(*shell->cmds);
			shell->cmds = NULL;
		}
		shell = NULL;
	}
}
