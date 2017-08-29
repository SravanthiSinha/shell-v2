#include "hsh.h"

/**
 * command_init - Adds  a command to  Command list
 * @command: The Command where the values are added.
 */
void command_init(Command **command)
{
	int i;
	Command *temp = NULL;
	Command *node = (Command *)malloc(sizeof(Command));

	if (node == NULL)
		exit(1);

	node->args = (char **)malloc(MAX_COMMANDS * sizeof(char *));
	for (i = 0; i < MAX_COMMANDS; i++)
		node->args[i] = NULL;
	node->redirect_type = HSH_OP_NONE;
	node->redirect_to = NULL;
	node->op = HSH_OP_NONE;
	node->path = NULL;
	node->next = NULL;
	if (*command == NULL)
		*command = node;
	else
	{
		temp = *command;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = node;
	}
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
 * print_commands - Prints the Command
 * @command: The Command to be printed
 *
 * Return: void
 */
void print_commands(Command *command)
{
	Command *node = NULL;

	node = command;
	while (node != NULL)
	{
		if (node->args)
		{
			printf("args:\n");
			print_array(node->args);
			if (node->redirect_to)
				printf("redirect to %s\n", node->redirect_to);
			if (node->path)
				printf("exe %s\n", node->path);
			printf("redirect_type %d operation %d\n", node->redirect_type, node->op);
		}
		node = node->next;
	}
}

/**
 * free_commands - Frees the Command
 * @head: The Command to be freed
 *
 * Return: void
 */
void free_commands(Command *head)
{
	Command *temp = NULL;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		if (temp->redirect_to)
		{
			free(temp->redirect_to);
			temp->redirect_to = NULL;
		}
		if (temp->path)
		{
			free(temp->path);
			temp->path = NULL;
		}
		free_array(temp->args);
		free(temp);
	}
	head = NULL;
}

/**
 * deleteCommand - Deletes the Command at specified position
 * @head_ref: The Command chain
 * @position: the position at which the command has to be deleted.
 * Return: void
 */
void deleteCommand(Command **head_ref, int position)
{
	Command *temp, *next;
	int i = 0;

	if (*head_ref == NULL)
		return;
	temp = *head_ref;
	if (position == 0)
	{
		*head_ref = temp->next;
		if (temp->redirect_to)
		{
			free(temp->redirect_to);
			temp->redirect_to = NULL;
		}
		if (temp->path)
		{
			free(temp->path);
			temp->path = NULL;
		}
		free_array(temp->args);
		free(temp);
		return;
	}
	for (i = 0; temp != NULL && i < position - 1; i++)
		temp = temp->next;
	if (temp == NULL || temp->next == NULL)
		return;
	next = temp->next->next;
	if (temp->next->redirect_to)
		FREE(temp->next->redirect_to);
	if (temp->next->path)
		FREE(temp->next->path);
	free_array(temp->next->args);
	free(temp->next); /*Free memory*/
	temp->next = next; /* Unlink the deleted node from list*/
}
