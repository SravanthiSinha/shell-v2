#include "builtins.h"

/**
 * change_dir - changes the directory based on the input
 * @shell : shell info
 * @args: This has the path to which the directory has to be changed to
 *
 * Return: On Success - HSH_SUCCESS, On Failure - HSH_FAILURE
 */
int change_dir(Shell *shell, char **args)
{
	int count = array_size(args), status = 0;
	char *path = NULL, *cwd = NULL;

	if (count > 1)
	{
		path = _strdup(args[1]);
		if (_strcmp(path, "-") == 0)
		{
			path = _getenv("OLDPWD");
			if (path == NULL)
				path = _getenv("PWD");
			printf("%s\n", path);
		}
	}
	else
		path = _strdup(shell->home);
	if (path)
	{
		cwd = _getenv("PWD");
		status = chdir(path) * -2;
		if (status == 0)
		{
			_setenv("OLDPWD", cwd, 1);
			_setenv("PWD", path, 1);
		}
		else
		{
			if (errno == EACCES || errno == ENOENT || errno == ELOOP ||
			    errno == ENOTDIR)
				print_error(shell, "cd", NULL, errno);
			else
				print_error(shell, "cd", path, HSH_CANNOT);
		}
		free(cwd);
		free(path);
	}
	return (status);
}
