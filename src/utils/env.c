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
	int i = 0, j = 0;

	if (name)
	{
		while (environ[i])
		{
			while (environ[i][j++] != '=')
				;
			if (strcmp(strndup(environ[i], j - 1), name) == 0)
			{
				return (environ[i] + j);
			}
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

	cnt = strlen(name) + strlen(value) + 2;
	env = malloc(sizeof(char) * cnt);
	if (env == NULL)
		return (-1);
	memset(env, '\0', cnt);
	strcpy(env, name);
	strcat(env, "=");
	strcat(env, value);
	while (environ[i] != NULL)
		i++;
	if (first)
	{
		envp = (char **)malloc(sizeof(char *) * (i + 2));
		if (envp == NULL)
			return (-1);
		first = 0;
		(void)memcpy(envp, environ, sizeof(char *) * i);
	}
	else
	{
		envp = (char **)realloc((char *)environ, sizeof(char *) * (i + 2));
		if (envp == NULL)
			return (-1);
	}
	environ = envp;
	environ[i] = strdup(env);
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
		env = _getenv(name);
		if (env != NULL)
		{
			if (!overwrite)
				return (0);
			if (strlen(env) >= strlen(value))
			{
				while ((*env++ = *value++))
					;
				return (0);
			}
			else
			{
				strcpy(env, value);
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
	char *env;
	int i = 0;

	env = _getenv(name);
	if (env == NULL)
		return (0);
	while (strcmp(strtok(environ[i], "="), name) != 0)
		i++;
	while (environ[i] != NULL)
	{
		if (environ[i + 1])
			swap(_getenv(environ[i]), _getenv(environ[i + 1]));
		else
			environ[i] = NULL;
		i++;
	}
	return (0);
}
