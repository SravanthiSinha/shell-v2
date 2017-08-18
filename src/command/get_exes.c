#include "hsh.h"

/**
 * is_path - Validates if the string is a path
 * @str: The string to be validated
 * Return: On Success - 1, On Failure - 0.
 */
int is_path(char *str)
{
	if (str && _strchr(str, '/'))
		return (1);
	return (0);
}

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

	cmd = shell->cmds;
	absolute_paths = _stringsplit(path_var, ':', NULL);
	while (absolute_paths && absolute_paths[i] && cmd)
	{
		if (!is_path(cmd->str))
		{
			path =  _stradd(absolute_paths[i], cmd->str, "/");
			if (exe_exists(path))
			{
				cmd->path = _strdup(path);
				cmd = cmd->next;
			}
			else
			{
				if (absolute_paths[i + 1] == NULL)
				{
					cmd->path = NULL;
					cmd = cmd->next;
					i = 0;
				}
			}
			i++;
		}
		else
		{
			cmd->path = _strdup(cmd->str);
			cmd->str = NULL;
			cmd = cmd->next;
		}
		free(path);
		path = NULL;
		free(path_var);
		path_var = NULL;
	}
	free_array(absolute_paths);
}
