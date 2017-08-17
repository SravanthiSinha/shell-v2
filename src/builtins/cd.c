#include "hsh.h"

/**
 * change_dir - changes the directory based on the input
 * @args: This has the path to which the directory has to be changed to
 *
 * Return: On Success - EXIT_SUCCESS, On Failure - EXIT_FAILURE
 */
int change_dir(char **args)
{
	int count = 0;
	char *path = NULL;

	count = array_size(args);
	if (count == 1) /* no path given*/
	{
		path = _strdup(_getenv("HOME"));
	}
	else if (count > 1)
	{
		path = _strdup(args[1]);
	}
	if (path != NULL)
	{
		if ((_strcmp(path, "-") != 0) && (_strcmp(path, ".") != 0) &&  count > 1)
		{
			if (path[0] == '/')
				path = _stradd(_getenv("PWD"), path, NULL);
			else
				path = _stradd(_getenv("PWD"), path, "/");
			if (exe_exists(path))
			{
				chdir(path);
				if ((_strcmp(args[1], "..") == 0))
				{
					_removeafter(path, '/');
					_removeafter(path, '/');
				}
				_setenv("PWD", path, 1);
			}
			else
			{
				print_error(args[0], args[1], HSH_NO_FILE_DIR);
			}
		}
		free(path);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
