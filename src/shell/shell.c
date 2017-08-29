#include "hsh.h"

/**
 * init_shell - Intialialises the shell with enviroanmental variables and
 * others defaults
 * @shell : shell info
 */
void init_shell(Shell *shell)
{
	shell->std[0] = -1;
	shell->std[1] = -1;
	shell->std[2] = -1;
	shell->isatty = isatty(fileno(stdin));
	shell->exit_status = HSH_SUCCESS;
	shell->cmdLine = NULL;
	shell->cmds = NULL;
	shell->program = NULL;
	shell->home = _getenv("HOME");
	shell->pwd = _getenv("PWD");
	shell->oldpwd = _getenv("OLDPWD");
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
		if (shell->pwd != NULL)
		{
			free(shell->pwd);
			shell->pwd = NULL;
		}
		if (shell->oldpwd != NULL)
		{
			free(shell->oldpwd);
			shell->oldpwd = NULL;
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
