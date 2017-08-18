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
			memcpy(out, s1, s1_len);
		memcpy(out + s1_len, s2, s2_len + 1);
	}
	free(s1);
	/*free(s2);*/
	return (out);
}
