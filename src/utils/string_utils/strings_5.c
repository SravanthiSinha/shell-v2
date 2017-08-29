#include "hsh.h"

/**
 * _strapp - Appends the s2 string to previous with s2 allocation
 * @s1: old String
 * @s2: new String
 *
 * Return: Created string with  old and new string concatinated.
 */
char *_strapp(char *s1, char *s2)
{
	size_t s1_len = 0, s2_len = 0;
	size_t out_len = 0;
	char *out = NULL;

	if (s1)
		s1_len = _strlen(s1);
	if (s2)
		s2_len = _strlen(s2);
	out_len = s1_len + s2_len + 1;
	out = malloc(out_len);
	if (out != NULL)
	{
		if (s1)
			_memcpy(out, s1, s1_len);
		_memcpy(out + s1_len, s2, s2_len + 1);
	}
	free(s1);
	return (out);
}


/**
 * ltrim - ltrims the string(removes leading char)
 * @src: C string
 * @c: character to be trimmed off
 * Return: left trimmed string
 */
char *ltrim(char *src, char c)
{
	char *original = src;
	char *p = original;
	int trimmed = 0;

	do {
		if (*original != c || trimmed)
		{
			trimmed = 1;
			*p++ = *original;
		}
	} while (*original++ != '\0');
	return (src);
}

/**
 * rtrim - right trims the string(removes succedding char)
 * @src: C string
 * @c: character to be trimmed off
 * Return: right trimmed string
 */
char *rtrim(char *src, char c)
{
	char *end;
	int len;

	len = _strlen(src);
	while (*src && len)
	{
		end = src + len - 1;
		if (c == *end)
			*end = 0;
		else
			break;
		len = _strlen(src);
	}
	return (src);
}

/**
 * trim - trims the string(removes leading and succeding char)
 * @src: C string
 * @c: character to be trimmed off
 * Return: trimmed string
 */
char *trim(char *src, char c)
{
	ltrim(src, c);
	rtrim(src, c);
	return (src);
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
