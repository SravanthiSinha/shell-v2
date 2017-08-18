#include "hsh.h"

/**
 * readCommandLine - prompts the user then reads & stores the input
 * @shell : shell info
 * Return: user input.
 */
char *readCommandLine(Shell *shell)
{
	char *input = NULL;
	char *buff = NULL;
	size_t len = 0;
	ssize_t read = 0;

	read = getline(&buff, &len, stdin);
	if (read == 1)
	{
		printPrompt(shell);
		return (readCommandLine(shell));
	}
	else if (read <= 0)
	{
		return (NULL);
	}
	input = _strdup(buff);
	free(buff);
	buff = NULL;
	input[_strlen(input) - 1] = '\0';
	return (input);
}

/**
 * main - The Entry point of the shell v2 program.
 * @argc: no of command line args
 * @argv: Input  to the program
 * Return: EXIT_SUCCESS, EXIT_FAILURE, or exit code
 */
int main(int argc, char __attribute__((unused)) **argv)
{
	Shell shell;
	int exit_status = EXIT_SUCCESS;

	if (argc != 1)
	{
		printf("Usage: hsh\n");
		exit(EXIT_FAILURE);
	}
	if (handle_sigaction() == -1)
	{
		printf("Failure installing sighandler\n");
		return (EXIT_FAILURE);
	}
	init_shell(&shell);
	while (exit_status == EXIT_SUCCESS)
	{
		printPrompt(&shell);
		shell.cmdLine = readCommandLine(&shell);
	  shell.cmds = parseCommand(shell.cmdLine, &exit_status);
		if (exit_status == EXIT_SUCCESS)
		{
			/*search & execution */
			get_exes(&shell);
			exit_status = validate_commands(shell.cmds);
			if (!shell.exit_code && exit_status)
				shell.exit_code = 1;
			if (exit_status == EXIT_SUCCESS)
				shell.exit_code = command_exec(&shell);
			if (shell.isatty)
				exit_status = EXIT_SUCCESS;
			else
				break;
			free_command(shell.cmds);
			free(shell.cmdLine);
			shell.cmds = NULL;
		}
	}
	terminate_shell(&shell);
	return (0);
}
