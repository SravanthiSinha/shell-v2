#include "hsh.h"

/**
 * init_shell - Intialialises the shell with enviroanmental variables and
 * others defaults
 * @shell : shell info
 */
void init_shell(Shell *shell)
{
	shell->stdin_fd = fileno(stdin);
	shell->isatty = isatty(shell->stdin_fd);
	shell->exit_code = 0;
	shell->cmdLine = NULL;
	shell->cmds = NULL;
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
		if (shell->cmdLine)
		{
			free(shell->cmdLine);
			shell->cmdLine = NULL;
		}
		if (shell->home)
		{
			free(shell->home);
			shell->home = NULL;
		}
		if (shell->pwd)
		{
			free(shell->pwd);
			shell->pwd = NULL;
		}
		if (shell->oldpwd)
		{
			free(shell->oldpwd);
			shell->oldpwd = NULL;
		}
		free_command(shell->cmds);
		shell = NULL;
	}
}
