#include "builtins.h"

/**
 * print_alias - fethces the alias and prints
 * @shell : shell info
 * @args: This has the command params
 * @index: index of params
 *
 * Return: On Success - 0, On Failure - 1
 */
int print_alias(Shell *shell, char **args, int index)
{
	char *alias = NULL;

	alias = hash_table_get(shell->aliases, args[index]);
	if (alias != NULL)
		printf("%s='%s'\n", args[index], alias);
	else
	{
		print_error(shell, args[0], args[index], HSH_COMMAND_NOT_FOUND);
		return (1);
	}
	return (0);
}

/**
 * alias - builtin command alias
 * @shell : shell info
 * @args: This has the command "env"
 *
 * Return: On Success - HSH_SUCCESS, On Failure - 2
 */
int alias(Shell *shell, char **args)
{
	int i = 1, error_occured = 0, pos = 0;
	char *key, *value;

	if (array_size(args) > 1)
	{
		while (*args && args[i])
		{
			if (_strchr(args[i], '=') == NULL) /*get the alias */
				error_occured = print_alias(shell, args, i);
			else /*set the alias */
			{
				if (args[i][0] != '=')
				{
					while (args[i][pos++] != '=')
						;
					key = _strndup(args[i], pos - 1);
					value = _strdup(args[i] + pos);
					hash_table_set(shell->aliases, key, value);
					free(key);
					free(value);
					pos = 0;
				}
				else
				{
					print_error(shell, args[0], args[i], HSH_COMMAND_NOT_FOUND);
					error_occured = 1;
				}
			}
			i++;
		}
	}
	else
	{
		shell->exit_status = HSH_SUCCESS;
		hash_table_print(shell->aliases);
	}
	return (error_occured ? 2 : HSH_SUCCESS);
}
