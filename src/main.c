#include "hsh.h"

/**
 * prompt_user - prompts the user then reads & stores the input
 * Return: user input.
 */
char *prompt_user(void)
{
	char *input = NULL;
	size_t len = 0;
	ssize_t read = 0;

	if (isatty(fileno(stdin)))
	{
		printf("($) ");
	}
	read = getline(&input, &len, stdin);
	if (read == 1)
		return (prompt_user());
	else if (read <= 0)
	{
		return (NULL);
	}
	input = _strdup(input);
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
	char *input = NULL;
	Command *cmds = NULL;
	int exit_status = EXIT_SUCCESS;
	int exit_prev = 0;

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
	while ((input = prompt_user()) != NULL && exit_status == EXIT_SUCCESS)
	{
		exit_status = get_commands(input, &cmds);
		if (exit_status == EXIT_SUCCESS)
		{
			get_exes(cmds);
			exit_status = validate_commands(cmds);
			if (!exit_prev && exit_status)
				exit_prev = 1;
			if (exit_status == EXIT_SUCCESS)
				exit_prev = execute_cmd(cmds, &exit_prev);
			exit_status = EXIT_SUCCESS;
			free_command(cmds);
			cmds = NULL;
		}
		free(input);
		input = NULL;
	}
	exit(exit_status);
}
