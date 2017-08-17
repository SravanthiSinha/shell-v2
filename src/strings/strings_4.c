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
