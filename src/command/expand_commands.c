#include "hsh.h"

/**
 * get_alias - gets the aliases recursivly
 * @shell : shell info
 * @key: key value of the alias
 * Return: alias
 */
char *get_alias(Shell *shell, char *key)
{
	char *alias = NULL;

	alias = hash_table_get(shell->aliases, key);
	if (alias && hash_table_get(shell->aliases, alias))
		return (get_alias(shell, alias));
	return (alias);
}

/**
 * expand_aliases - substitues the command with respective alias
 * @shell : shell info
 * Return: Nothing
 */
void expand_aliases(Shell *shell)
{
	Command *cmd = NULL;
	char *alias = NULL;

	cmd = *(shell->cmds);
	while (cmd)
	{
		alias = get_alias(shell, cmd->args[0]);
		if (alias)
		{
			free(cmd->args[0]);
			cmd->args[0] = _strdup(alias);
			free(alias);
			alias = NULL;
		}
		cmd = cmd->next;
	}
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
				free(path);
				path = NULL;
				i++;
			}
		}
		cmd = cmd->next;
	}
	free(path_var);
	path_var = NULL;
	free_array(absolute_paths);
}

/**
 * expand_commands - substitues the command with respective alias & fills paths
 * @shell : shell info
 * Return: Nothing
 */
void expand_commands(Shell *shell)
{
	expand_aliases(shell);
	get_exes(shell);
}
