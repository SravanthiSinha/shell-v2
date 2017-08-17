#include "hsh.h"


/**
 * command_add - Adds the value to the command of Command
 * @command: The Command where the values are added.
 * @content: The value to be added.
 * @input: user input to be converted in to command.
 * Return: on success: EXIT_SUCCESS - 0 , on Failure: EXIT_FAILURE -2.
 */
int command_add(Command **command, char *content, char *input)
{
	Command *head = NULL;
	Command *node = NULL;

	head = *command;
	if (head == NULL)
	{
		head = (Command *)malloc(sizeof(Command));
		if (head == NULL)
			return (EXIT_FAILURE);
		head->str = _strdup(content);
		head->args = _stringsplit(input, ' ', NULL);
		head->builtin = 0;
		head->next = NULL;
		*command = head;
		return (EXIT_SUCCESS);
	}
	else
	{
		node = (Command *)malloc(sizeof(Command));
		if (node == NULL)
			return (1);
		node->str = _strdup(content);
		node->builtin = 0;
		node->args = _stringsplit(input, ' ', NULL);
		node->next = *command;
		*command = node;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

/**
 * command_size - gets the  size of Command list.
 * @command: The list of Command whose size has to be measured.
 *
 * Return: size of the command of Command.
 */
int command_size(Command *command)
{
	Command *node = NULL;
	int size;

	size = 0;
	node = command;
	while (node != NULL)
	{
		size++;
		node = node->next;
	}

	return (size);
}

/**
 * print_command - Prints the Command
 * @command: The Command to be printed
 *
 * Return: void
 */
void print_command(Command *command)
{
	Command *node = NULL;

	node = command;
	while (node != NULL)
	{
		printf("command %s\n", node->str);
		if (node->args)
			print_array(node->args);
		printf("path %s\n", node->path);
		node = node->next;
	}
}

/**
 * free_command - Frees the Command
 * @head: The Command to be freed
 *
 * Return: void
 */
void free_command(Command *head)
{
	Command *temp = NULL;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->str);
		free_array(temp->args);
		free(temp);
	}
	head = NULL;
}
