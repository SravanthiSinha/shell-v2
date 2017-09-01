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
		free(buff);
		buff = NULL;
		return (NULL);
	}
	input = _strdup(get_str(buff));
	free(buff);
	buff = NULL;
	if (input && _strlen(input))
		input[_strlen(input) - 1] = '\0';
	else
	{
		free(input);
		return (NULL);
	}
	return (input);
}

/**
 * main - The Entry point of the shell v2 program.
 * @argc: no of command line args
 * @argv: Input  to the program
 * Return: HSH_SUCCESS, HSH_FAILURE, or exit_status
 */
int main(int argc, char *argv[])
{
	Shell shell;
	Command *cmds = NULL;
	int status = 0;

	if (argc != 1)
	{
		printf("Usage: hsh\n");
		exit(HSH_FAILURE);
	}
	if (handle_sigaction() == -1)
	{
		printf("Failure installing sighandler\n");
		return (HSH_FAILURE);
	}
	init_shell(&shell, argv);
	while (1)
	{
		printPrompt(&shell);
		shell.cmdLine = readCommandLine(&shell);
		if (shell.cmdLine && _strlen(shell.cmdLine))
		{
			shell.lineno++;
			lexer_run(&shell, &cmds);
			shell.cmds = &cmds;
			if (shell.cmds)
			{
				get_exes(&shell);
				exec_commands(&shell);
				free_commands(*shell.cmds);
				shell.cmds = NULL;
			}
			free(shell.cmdLine);
			shell.cmdLine = NULL;
		}
		else
			break; /*reached eof*/
	}
	status = shell.exit_status;
	terminate_shell(&shell);
	return (status);
}
