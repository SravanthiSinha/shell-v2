#include "builtins.h"


/**
 * get_op_func - returns the function pointer of the corresponding builtin
 * @name: The builtin
 * Return: on success: valid function pointer - 0 , on Failure: NULL.
 */
int (*get_op_func(char *name))(Shell *, char **)
{
	int i;
	char *builtins[] = {"env", "cd"};
	funcPtr p[2] = {printenv, change_dir};

	for (i = 0; i < 2; i++)
		if (_strcmp(builtins[i], name) == 0)
			return (*p[i]);
	return (NULL);
}

/**
 * handle_builtins - Execute the builtins
 * @cmd: The builtin
 * @shell : shell info
 * Return: On Success - EXIT_SUCCESS, On Failure - EXIT_FAILURE.
 */
int handle_builtins(Shell *shell, Command *cmd)
{
	int count = 0;
	int (*a)(Shell *, char **);

	if (_strcmp(cmd->str, "exit") == 0)
	{
		count = array_size(cmd->args);
		if (count == 1)
			do_exit(shell, shell->exit_code);
		if (count > 2 && are_numbers(cmd->args + 1))
		{
			print_error(cmd->str, NULL, HSH_TOO_MANY_ARGS);
			shell->exit_code = 1;
			return (EXIT_FAILURE);
		}
		else
			do_exit(shell, _atoi(cmd->args[1]));
	}
	a = get_op_func(cmd->str);
	if (a == NULL)
	{
		print_error(cmd->str, NULL, HSH_NOT_FOUND);
		shell->exit_code = 1;
		return (EXIT_FAILURE);
	}
	return ((*a)(shell, cmd->args));
}

/**
 * command_exec - Execute the command
 * @shell : shell info
 * Return: On Success - EXIT_SUCCESS, On Failure - EXIT_FAILURE.
 */
int command_exec(Shell *shell)
{
	Command *cmd = NULL;
	int  child_pid, status;

	cmd = shell->cmds;
	while (cmd)
	{
		if (cmd->builtin)
		{
			handle_builtins(shell, cmd);
			cmd = cmd->next;
		}
		else
		{
			child_pid = fork();
			if (child_pid == -1)
			{
				perror("fork");
				exit(1);
			}
			if (child_pid == 0)
			{
				execve(cmd->path, cmd->args, NULL);
			}
			if (child_pid != 0)
			{
				wait(&status);
				cmd = cmd->next;
			}
		}
	}
	return (EXIT_SUCCESS);
}
