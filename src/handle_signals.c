#include "hsh.h"

/**
 * sigint_handler - Catch SIGINT (CTRL+C)
 * @signum: Signal number
 */
void sigint_handler(int signum)
{
	(void)signum;
}

/**
 * handle_sigaction - a function that set a handler for the signal SIGINT
 * Return: 0 on success, or -1 on error.
 */

int handle_sigaction(void)
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_handler = sigint_handler;
	return (sigaction(SIGINT, &sa, NULL));
}
