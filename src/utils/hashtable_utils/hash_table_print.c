#include "hsh.h"

/**
 * hash_table_print - prints a hash table
 * @ht: pointer to hash table
 * Return: nothing
 **/
void hash_table_print(const hash_table_t *ht)
{
	unsigned long int i;
	hash_node_t *node;

	node = NULL;
	if (ht != NULL)
	{
		if (ht->array)
		{
			for (i = 0; i < ht->size; i++)
			{
				node = ht->array[i];
				while (node != NULL)
				{
					printf("%s='%s'\n", node->key, node->value);
					node = node->next;
				}
			}
		}
	}
}
