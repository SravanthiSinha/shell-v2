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
		return (NULL);
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
 * Return: HSH_SUCCESS, HSH_FAILURE, or exit_status
 */
int main(int argc, char *argv[])
{
	Shell shell;
	Command *cmds = NULL;

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
	init_shell(&shell);
	shell.program = _strdup(argv[0]);
	while (1)
	{
		printPrompt(&shell);
		shell.cmdLine = readCommandLine(&shell);
		if (shell.cmdLine)
		{
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
	terminate_shell(&shell);
	return (0);
}
