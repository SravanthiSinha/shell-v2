#include "hsh.h"
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

/**
 * _memset - The _memset function fills the first n bytes of the memory area
 * pointed to by s with the bytes b
 * @s: bytes to be filled in
 * @b: bytes to be filled
 * @n: no of bytes
 *
 * Return: A pointer to the memory area s
 */

char *_memset(char *s, char b, unsigned int n)
{
	char *p;

	p = s;
	while (n--)
		*p++ = b;
	return (s);
}
