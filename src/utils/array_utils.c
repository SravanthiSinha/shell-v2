#include "hsh.h"

/**
 * array_size - gets the size of the array.
 * @arr: The array whose size has to be measured.
 *
 * Return: size of the command of array.
 */
int array_size(char **arr)
{
	int i = 0;

	while (arr && arr[i])
	{
		i++;
	}
	return (i);
}

/**
 * print_array - Prints the array
 * @arr: The array to be printed
 *
 * Return: void
 */
void print_array(char **arr)
{
	int i = 0;

	while (arr && arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

/**
 * free_array - Frees the array
 * @arr: The array to be freed
 *
 * Return: void
 */
void free_array(char **arr)
{
	int i = 0;
	int count = array_size(arr);

	while (i < count)
	{
		free(arr[i]);
		i++;
	}
	if (arr)
		free(arr);
	arr = NULL;
}
