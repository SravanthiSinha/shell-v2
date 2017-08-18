#include "builtins.h"

/**
* do_exit - Exits the program
* @shell: shell info
* @exit_status: The status to be exited with
*
* Return: Nothing
*/
void do_exit(Shell *shell, int exit_status)
{
	terminate_shell(shell);
	exit(exit_status);
}
