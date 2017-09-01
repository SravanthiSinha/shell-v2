#include "hsh.h"

/**
 * get_exes - Fills the command with respective exes of the command.
 * @shell : shell info
 * Return: Nothing
 */
void get_exes(Shell *shell)
{
	int i = 0;
	char **absolute_paths = NULL, *path = NULL, *path_var = _getenv("PATH");
	Command *cmd = NULL;

	cmd = *(shell->cmds);
	absolute_paths = path_var != NULL ? _stringsplit(path_var, ':', NULL) : NULL;
	while (cmd)
	{
		if (is_path(cmd->args[0]))
			cmd->path = _strdup(cmd->args[0]);
		else
		{
			i = 0;
			while (absolute_paths && absolute_paths[i])
			{
				path =  _stradd(absolute_paths[i], cmd->args[0], "/");
				if (exe_exists(path))
				{
					cmd->path = _strdup(path);
					free(path);
					path = NULL;
					break;
				}
				i++;
			}
		}
		cmd = cmd->next;
	}
	free(path_var);
	path_var = NULL;
	free_array(absolute_paths);
}
