#include "hsh.h"

/**
 * is_dir - Verifies if a file path is a directory
 * @filepath: file path
 *
 * Return: on success: 1 , on Failure:0.
 */
int is_dir(const char *filepath)
{
	struct stat path_stat;

	lstat(filepath, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

/**
 * exe_exists - Validates if the path exsits
 * @path: The path to be validated
 * Return: On Success - 1, On Failure - 0.
 */
int exe_exists(char *path)
{
	struct stat fileStat;

	if (lstat(path, &fileStat) == -1)
		return (0);
	else
		return (1);
}


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
