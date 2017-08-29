#include "hsh.h"
/**
 * _realloc - function changes the size of the memory block pointed to by
 * ptr to size bytes
 * @ptr: the pointer to be reallocted
 * @size: the no of bytes to be reallocted
 * @msize: the no of bytes to be  previously allocted
 * Return: a pointer to the newly allocated memory.
 */
void *_realloc(void *ptr, size_t size, size_t msize)
{
	void *newptr = NULL;

	if (size <= msize)
		return (ptr);
	newptr = malloc(size);
	if (newptr)
	{
		_memcpy(newptr, ptr, msize);
		free(ptr);
		return (newptr);
	}
	return (NULL);
}
