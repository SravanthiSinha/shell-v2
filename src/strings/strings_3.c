#include "hsh.h"

/**
 * _memcmp - compares the first n characters of the object pointed to by s1
 * to the first n characters of the object pointed to by s2.
 * @s1: string @s1
 * @s2: string @s2
 * @n: no of characters to be compated
 *
 * Return: Integer greater than, equal to, or less than zero, accordingly as
 * the object pointed to by s1 is greater than, equal to, or less than the
 * object pointed to by s2.
 */
int _memcmp(const void *s1, const void *s2, unsigned int n)
{
	const unsigned char *p1 = s1, *p2 = s2;

	while (n--)
	{
		if (*p1 != *p2)
			return (*p1 - *p2);
		p1++, p2++;
	}
	return (0);
}

/**
 * _strstr - Finds the 1st occurrence of the substring needle in
 * the string haystack.
 * @haystack: string to be searched in
 * @needle: string to be looked for in @haystack
 *
 * Return: A pointer to the beginning of the substring, or NULL
 * if the substring is not found.
 */
char *_strstr(char *haystack, char *needle)
{
	int n;

	n = _strlen(needle);
	while (*haystack)
		if (!_memcmp(haystack++, needle, n))
			return (haystack - 1);
	return (0);
}

/**
 * _strcpy - The  _strcpy()  function  copies the string pointed to by src,
 * including the terminating null byte ('\0') to the buffer pointed to by dest.
 * @dest: string to be copied into
 * @src: string to be copied
 *
 * Return: a pointer to the destination string dest.
 */
char *_strcpy(char *dest, const char *src)
{
	int i;

	i = 0;
	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}


/**
 * nwords - gets the no of words present in a string delimited by a @delim
 * @str: This is the string where the  no of words has to be calculated.
 * @delim: the delimeter
 * Return: Number of words in the string s.
 */
int nwords(char *str, char delim)
{
	int i, n, len;

	i = 0;
	n = 0;
	len = _strlen(str);
	while (str[i] != '\0')
	{
		if (str[i] != delim && str[i + 1] == delim && i < len)
			n++;
		i++;
	}
	if (str[i - 1] != delim && str[i] == '\0')
		n++;
	return (n);
}

/**
 * _stringsplit - The  _stringsplit() function splits the string delimeted by
 * a delimeter and returns the array of strings
 * @str: This is the string which has to be split
 * @delim: the delimeter
 * @count: the no of words present in a string delimited by a @delim
 * Return: a pointer to the array of string split.
 */
char **_stringsplit(char *str, char delim, int *count)
{
	char **tab;
	int i, j, k, l, m, n;

	k = 0;
	l = 0;
	m = 0;
	n = nwords(str, delim);
	tab = (char **)malloc((n + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	for (i = 0; i < n; i++)
	{
		j = 0;
		l = 0;
		while (str[k] != delim && str[k] != '\0')
		{
			j++;
			k++;
		}
		tab[i] = (char *)malloc(sizeof(char) * (j + 1));
		if (tab[i] == NULL)
			return (NULL);
		while (l < j)
		{
			tab[i][l] = str[m];
			l++;
			m++;
		}
		tab[i][l] = '\0';

		while (str[k] == delim && str[k] != '\0')
		{
			k++;
			m++;
		}
	}
	tab[i] = NULL;
	if (count)
		*count = i;
	return (tab);
}
