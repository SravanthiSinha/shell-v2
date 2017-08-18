#include "builtins.h"

/**
 * change_dir - changes the directory based on the input
 * @shell : shell info
 * @args: This has the path to which the directory has to be changed to
 *
 * Return: On Success - EXIT_SUCCESS, On Failure - EXIT_FAILURE
 */
int change_dir(Shell *shell, char **args)
{
	int count = 0;
	char *path = NULL;
	char *abspath = NULL;

	count = array_size(args);
	if (count == 1) /* no path given*/
		abspath = _strdup(shell->home);
	else if (count > 1)
		path = _strdup(args[1]);
	if (path)
	{
		if ((_strcmp(path, "-") != 0) && (_strcmp(path, ".") != 0))
		{
			if (path[0] == '/' && count > 1)
				abspath = _stradd(shell->pwd, path, NULL);
			else if (count > 1)
				abspath = _stradd(shell->pwd, path, "/");
			if (exe_exists(abspath))
			{
				chdir(abspath);
				if ((_strcmp(args[1], "..") == 0))
				{
					_removeafter(abspath, '/');
					_removeafter(abspath, '/');
				}
				_setenv("PWD", abspath, 1);
				_setenv("OLDPWD", shell->pwd, 1);
				shell->oldpwd = _strapp(shell->oldpwd, shell->pwd);
				shell->pwd = _strapp(shell->pwd, abspath);
			}
			else
			print_error(args[0], args[1], HSH_NO_FILE_DIR);
		}
		free(path);
		free(abspath);
		path = NULL;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
