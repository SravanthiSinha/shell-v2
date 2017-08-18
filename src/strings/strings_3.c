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
 * _memcpy - copiesthe first n characters of the object pointed to by s1
 * to the first n characters of the object pointed to by s2.
 * @dest: string @dest
 * @src: string @src
 * @n: no of characters to be compated
 *
 * Return: Integer greater than, equal to, or less than zero, accordingly as
 * the object pointed to by s1 is greater than, equal to, or less than the
 * object pointed to by s2.
 */
void _memcpy(void *dest, void *src, size_t n)
{
	size_t i = 0;
	char *csrc = (char *)src;
	char *cdest = (char *)dest;

	for (i = 0; i < n; i++)
		cdest[i] = csrc[i];
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
 * _strndup - The  _strndup()  function  copies the string pointed to by src,
 * at most n bytes of  src  are copied.
 * to  the  buffer  pointed  to  by  dest.
 * @s: string to be copied
 * @n: number of bytes to be copied
 *
 * Return: a pointer to the destination string dest.
 */
char *_strndup(char *s, size_t n)
{
	char *result;
	unsigned int len = _strlen(s);

	if (n < len)
		len = n;

	result = (char *)malloc(len + 1);
	if (!result)
		return (0);

	result[len] = '\0';
	return ((char *)memcpy(result, s, len));
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
