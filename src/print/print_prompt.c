#include "hsh.h"

/**
 * printPrompt - prompts the user
 * @shell : shell info
 * Return: Nothing.
 */
void printPrompt(Shell *shell)
{
	if (shell && shell->isatty)
	{
		printf("($) ");
	}
}
