#include "hsh.h"
/**
 * ltrim - ltrims the string(removes leading .)
 * @src: node1
 *
 * Return: ltrimmed string
 */
char *ltrim(char *src)
{
	char *original = src;
	char *p = original;
	int trimmed = 0;

	do {
		if (*original != '.' || trimmed)
		{
			trimmed = 1;
			*p++ = *original;
		}
	} while (*original++ != '\0');
	return (src);
}

/**
 * _stradd - Returns a string which is concatination of s1 & s2
 * @s1: C string
 * @s2: C string
 * @delim: deimater
 * Return: A pointer string which is concatination of s1 & s2
 */
char *_stradd(const char *s1, const char *s2, char *delim)
{
	int len = 0;
	char *str = NULL;

	if (s1)
		len = _strlen(s1) + 1;
	if (s2)
		len += _strlen(s2);
	if (delim)
		len += _strlen(delim);
	str = (char *)malloc(sizeof(char) * len);
	if (s1)
		_strcpy(str, s1);
	if (delim)
		_strcat(str, delim);
	if (s2)
		_strcat(str, s2);
	return (str);
}

/**
 * _removeafter - Removes content after delim
 * @s: C string
 * @delim: deimater
 * Return: Nothing
 */
void _removeafter(char *s, char delim)
{
	char *del = &s[_strlen(s)];

	while (del > s && *del != delim)
		del--;

	if (*del == delim)
		*del = '\0';
}
