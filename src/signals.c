#include "hsh.h"


/**
 * sigquit_handler - handler for the signal SIGQUIT
 * @signum: signal number
 * Return : void.
 */
void sigquit_handler(int __attribute__((unused)) signum)
{
	exit(EXIT_SUCCESS);
}

/**
 * handle_sigaction - a function that set a handler for the signal SIGQUIT
 * Return: 0 on success, or -1 on error.
 */

int handle_sigaction(void)
{
	struct sigaction sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_handler = sigquit_handler;

	return (sigaction(SIGQUIT, &sa, NULL));
}
