#include "hsh.h"


/**
 * get_op_func - returns the function pointer of the corresponding builtin
 * @name: The builtin
 * Return: on success: valid function pointer - 0 , on Failure: NULL.
 */
int (*get_op_func(char *name))(char **)
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
 * @prev_status: The exit status of the previous command
 * Return: On Success - EXIT_SUCCESS, On Failure - EXIT_FAILURE.
 */
int handle_builtins(Command *cmd, int *prev_status)
{
	int count = 0;
	int (*a)(char **);

	if (_strcmp(cmd->str, "exit") == 0)
	{
		count = array_size(cmd->args);
		if (count == 1)
			do_exit(*prev_status);
		if (count > 2 && are_numbers(cmd->args + 1))
		{
			print_error(cmd->str, NULL, HSH_TOO_MANY_ARGS);
			*prev_status = 1;
			return (EXIT_FAILURE);
		}
		else
			do_exit(_atoi(cmd->args[1]));
	}
	a = get_op_func(cmd->str);
	if (a == NULL)
	{
		print_error(cmd->str, NULL, HSH_NOT_FOUND);
		*prev_status = 1;
		return (EXIT_FAILURE);
	}
	return ((*a)(cmd->args));
}

/**
 * execute_cmd - Execute the command
 * @cmds: The list of commands to be executed
 * @prev_status: The exit status of the previous command
 * Return: On Success - EXIT_SUCCESS, On Failure - EXIT_FAILURE.
 */
int execute_cmd(Command *cmds, int *prev_status)
{
	Command *cmd = NULL;
	int  child_pid, status;

	cmd = cmds;
	while (cmd)
	{
		if (cmd->builtin)
		{
			handle_builtins(cmd, prev_status);
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
