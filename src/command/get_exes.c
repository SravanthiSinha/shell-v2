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
 * @cmds: The list of commands to be executed
 * Return: Nothing
 */
void get_exes(Command *cmds)
{
	int i = 0;
	char **absolute_paths = NULL, *path = NULL;
	Command *cmd = NULL;

	cmd = cmds;
	absolute_paths = _stringsplit(_getenv("PATH"), ':', NULL);
	while (absolute_paths && absolute_paths[i] && cmd)
	{
		if (!is_path(cmd->str))
		{
			path = (char *)malloc(
				sizeof(char) * (_strlen(absolute_paths[i]) + _strlen(cmd->str) + 2));
			_strcpy(path, absolute_paths[i]);
			_strcat(path, "/");
			_strcat(path, cmd->str);
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
	}
	free_array(absolute_paths);
}
