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
 * swap - swaps the strings in place
 * @a: pointer to string a
 * @b: pointer to string b
 * Return: nothing.
 */
void swap(char *a, char *b)
{
	char *c;

	c = b;
	b = a;
	a = c;
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
