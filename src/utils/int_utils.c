#include "hsh.h"

/**
 * are_numbers - Verifies if a input contains only numbers.
 * @args: array of strings.
 *
 * Return: on success: 1 , on Failure:0.
 */
int are_numbers(char **args)
{
	int i = 0;

	while (args[i])
	{
		if (!_atoi(args[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * isNumericChar - Verifies if a input is anumbers.
 * @x: char to be validated
 *
 * Return: on success: 1 , on Failure:0.
 */
int isNumericChar(char x)
{
	return ((x >= '0' && x <= '9') ? 1 : 0);
}

/**
 * _atoi - converts string to an int.
 * @input: string to be converted.
 *
 * Return: on success:converted int, on Failure:0.
 */
int _atoi(char *input)
{
	int res;
	int sign;
	int i;
	char *str;

	res = 0;
	sign = 1;
	i = 0;
	str = _strdup(input);
	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}
	for (; str[i] != '\0'; ++i)
	{
		if (isNumericChar(str[i]) == 0)
			return (0);
		res = res * 10 + str[i] - '0';
	}
	free(str);
	return (sign * res);
}
