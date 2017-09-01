#include "builtins.h"

/**
 * command_exec_child -  executes the command
 * @shell : shell info
 * @cmd: command to be executed.
 */
void command_exec_child(Shell *shell, Command *cmd)
{
	if (cmd->path)
	{
		execve(cmd->path, cmd->args, NULL);
	}
	print_error(shell, cmd->args[0], NULL, HSH_COMMAND_NOT_FOUND);
	terminate_shell(shell);
	_exit(127);
}

/**
 * fork_exec - forks and executes the command
 * @shell : shell info
 * @cmd: command to be executed.
 * Return: On Success - HSH_SUCCESS, On Failure - HSH_FAILURE.
 */
int fork_exec(Shell *shell, Command *cmd)
{
	int status = 0, child_pid = fork();

	if (child_pid == 0)
	{
		if (cmd->redirect_type == HSH_OP_REDIRECT_PIPE_OUT)
		{
			if (dup2(shell->pipefd[WRITE_END], STDOUT_FILENO) == -1)
			{
				perror("hsh: dup2");
				_exit(HSH_FAILURE);
			}
			close(shell->pipefd[READ_END]);
			close(shell->pipefd[WRITE_END]);
		}
		else if (cmd->redirect_type == HSH_OP_REDIRECT_PIPE_IN)
		{
			if (dup2(shell->pipefd[READ_END], STDIN_FILENO) == -1)
			{
				perror("hsh: dup2");
				_exit(HSH_FAILURE);
			}
			close(shell->pipefd[READ_END]);
			close(shell->pipefd[WRITE_END]);
		}
		command_exec_child(shell, cmd);
	}
	if (child_pid != 0)
	{
		if (cmd->redirect_type == HSH_OP_REDIRECT_PIPE_OUT)
			close(shell->pipefd[WRITE_END]);
		else if (cmd->redirect_type == HSH_OP_REDIRECT_PIPE_IN)
			close(shell->pipefd[READ_END]);
		wait(&status);
		shell->exit_status = WEXITSTATUS(status);
	}
	return (status);
}

/**
 * exec_command - Execute the command
 * @shell : shell info
 * @cmd: command to be executed.
 */
void exec_command(Shell *shell, Command *cmd)
{
	if (cmd && cmd->args[0])
	{
		if (is_builtin(cmd->args[0]))
			shell->exit_status = handle_builtins(shell, cmd);
		else
			fork_exec(shell, cmd);
	}
}


/**
 * restore_std_fd - Restored the I/O and redirection
 * @shell : shell info
 */
void restore_std_fd(Shell *shell)
{
	if (shell->std[0] != -1)
	{
		/* Restore stdin */
		dup2(shell->std[0], STDIN_FILENO);
		close(shell->std[0]);
		shell->std[0] = -1;
	}
	if (shell->std[1] != -1)
	{
		/* Restore stdout */
		dup2(shell->std[1], STDOUT_FILENO);
		close(shell->std[1]);
		shell->std[1] = -1;
	}
	if (shell->std[2] != -1)
	{
		/* Restore stderr */
		dup2(shell->std[2], STDERR_FILENO);
		close(shell->std[2]);
		shell->std[2] = -1;
	}
	unlink("shell_heredoc_buffer");
}

/**
 * exec_commands - Executes the command accordingly
 * @shell : shell info
 */
void exec_commands(Shell *shell)
{
	Command *cmds = *(shell->cmds);
	Command *cmd = cmds;
	int op = 0;

	while (cmd)
	{
		if (!handle_redirections(shell, cmd))
			shell->exit_status = 2;
		else
			exec_command(shell, cmd);
		restore_std_fd(shell);
		if (((shell->exit_status == HSH_FAILURE) && (cmd->op == HSH_OP_AND)) ||
		    ((shell->exit_status == HSH_SUCCESS) && (cmd->op == HSH_OP_OR)))
		{
			op = cmd->op;
			while (cmd && cmd->next && op == cmd->op)
			{
				cmd = cmd->next;
			}
		}
		cmd = cmd->next;
	}
}
