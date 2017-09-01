#include "hsh.h"


/**
 * _getenv - The  _getenv() function searches the environment list to find
 * the environment variable name, and returns a pointer to the corresponding
 * value string
 * @name: variable name.
 *
 * Return: A pointer to the value in the environment,
 * or NULL if there is no match.
 */
char *_getenv(const char *name)
{
	int i = 0;
	char **arr = NULL;
	char *path = NULL;

	if (name)
	{
		while (environ[i])
		{
			arr = _stringsplit(environ[i], '=', 0);
			if (arr && (_strcmp(arr[0], name) == 0))
			{
				path = _strdup(arr[1]);
				free_array(arr);
				return (path);
			}
			free_array(arr);
			i++;
		}
	}
	return (NULL);
}

/**
 * _findenv - The  _findenv() function searches the environment list to find
 * the environment variable name, and returns the corresponding value
 * @name: variable name.
 *
 * Return: A pointer to the value in the environment,
 * or NULL if there is no match.
 */
char *_findenv(const char *name)
{
	int i = 0, j = 0;
	char *n = NULL;

	if (name)
	{
		while (environ[i])
		{
			while (environ[i][j++] != '=')
				;
			n = _strndup(environ[i], j - 1);
			if (_strcmp(n, name) == 0)
			{
				free(n);
				return (environ[i] + j);
			}
			free(n);
			i++;
			j = 0;
		}
	}
	return (NULL);
}

/**
 * _putenv - The  _putenv() function adds or changes the value of environment
 * variables.  The argument string is of the form name=value.  If name does not
 * already exist in the environment, then string is added to the environment.
 * @name: variable name.
 * @value: the value to be assigned to the variable name.
 * Return: zero on success, or -1 if an error occurs.
 */
int _putenv(const char *name, const char *value)
{
	int cnt = 0, i = 0;
	char **envp, *env;
	static int first = 1;

	cnt = _strlen(name) + _strlen(value) + 2;
	env = malloc(sizeof(char) * cnt);
	if (env == NULL)
		return (-1);
	_memset(env, '\0', cnt);
	_strcpy(env, name);
	_strcat(env, "=");
	_strcat(env, value);
	while (environ[i] != NULL)
		i++;
	if (first)
	{
		envp = (char **)malloc(sizeof(char *) * (i + 2));
		if (envp == NULL)
			return (-1);
		first = 0;
		(void)_memcpy(envp, environ, sizeof(char *) * i);
	}
	else
	{
		envp = (char **)_realloc((char *)environ, sizeof(char *) * (i + 2),
		sizeof(envp));
		if (envp == NULL)
			return (-1);
	}
	environ = envp;
	environ[i] = _strdup(env);
	environ[i + 1] = NULL;
	return (0);
}

/**
 * _setenv - The _setenv() function adds the variable name to the environment
 * with the value value, if name does not already exist. If name does exist in
 * he environment, then its value is changed to value if overwrite is nonzero;
 * if overwrite is zero, then the value of name  is  not  changed.
 * @name: variable name.
 * @value: the value to be assigned to the variable name.
 * @overwrite: if the value has to be overwriten
 * Return: zero on success, or -1 if an error occurs.
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	char *env;

	if (name != NULL)
	{
		env = _findenv(name);
		if (env != NULL)
		{
			if (!overwrite)
				return (0);
			if (_strlen(env) >= _strlen(value))
			{
				while ((*env++ = *value++))
					;
				return (0);
			}
			else
			{
				_strcpy(env, value);
				return (0);
			}
		}
		else
		{
			return (_putenv(name, value));
		}
	}
	return (-1);
}

/**
 * _unsetenv - The _unsetenv() function removes the variable name to
 * the environment with the name as name
 * @name: variable name.
 * Return: zero on success
 */
int _unsetenv(const char *name)
{
	const size_t len = _strlen(name);
	char **ep, **dp;

	for (ep = environ; *ep; ++ep)
		if (!_strncmp(*ep, name, len) && (*ep)[len] == '=')
		{
			dp = ep;
			do
				dp[0] = dp[1];
			while (*dp++);
		}
	return (0);
}
