#include "hsh.h"

/**
 * handle_out_redirection - creates a dup for the STDOUT_FILENO
 * @shell : shell info
 * @cmd: command to be executed.
 * Return: On Success - HSH_FAILURE, On Failure - HSH_SUCCESS.
 */
int handle_out_redirection(Shell *shell, Command *cmd)
{
	int fd;
	int flags = O_WRONLY | O_CREAT;
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;

	if (cmd->redirect_type == HSH_OP_REDIRECT_OUT)
		flags |= O_TRUNC;
	else
		flags |= O_APPEND;
	fd = open(cmd->redirect_to, flags, mode);
	if (fd == -1)
	{
		perror("hsh: open");
		shell->exit_status = 1;
		return (0);
	}
	shell->std[1] = dup(STDOUT_FILENO);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("hsh: dup2");
		shell->exit_status = 1;
		return (0);
	}
	close(fd);
	return (1);
}

/**
 * handle_pipe - creates a pipe for the I/O
 * @shell : shell info
 * Return: On Success - HSH_FAILURE, On Failure - HSH_SUCCESS.
 */
int handle_pipe(Shell *shell)
{
	if (pipe(shell->pipefd) == -1)
	{
		perror("hsh: pipe");
		shell->exit_status = 1;
		return (0);
	}
	return (1);
}

/**
 * handle_in_redirection - creates a dup for the STDIN_FILENO
 * @shell : shell info
 * @out_file: out put filename
 * Return: On Success - HSH_FAILURE, On Failure - HSH_SUCCESS.
 */
int handle_in_redirection(Shell *shell, char *out_file)
{
	int fd;
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;

	fd = open(out_file, O_RDONLY, mode);
	if (fd == -1)
	{
		perror("hsh: open");
		shell->exit_status = 1;
		return (0);
	}
	shell->std[0] = dup(STDIN_FILENO);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("hsh: dup2");
		shell->exit_status = 1;
		return (0);
	}
	close(fd);
	return (1);
}

/**
 * handle_heredoc - HANDLES THE here doc
 * @shell : shell info
 * @cmd: command to be executed.
 * Return: On Success - HSH_FAILURE, On Failure - HSH_SUCCESS.
 */
int handle_heredoc(Shell *shell, Command *cmd)
{
	int fd;
	int flags = O_WRONLY | O_CREAT | O_TRUNC;
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
	char *line = NULL;
	size_t size;
	ssize_t ret;

	fd = open("shell_heredoc_buffer", flags, mode);
	if (fd == -1)
	{
		perror("hsh: open");
		shell->exit_status = 1;
		return (0);
	}
	while (1)
	{
		printf("> ");
		ret = getline(&line, &size, stdin);
		if (ret <= 0)
			break;
		if (_strcmp(line, cmd->redirect_to) == 0 ||
		    (_strncmp(line, cmd->redirect_to, _strlen(cmd->redirect_to)) == 0 &&
		     line[_strlen(cmd->redirect_to)] == '\n'))
		{
			free(line);
			break;
		}
		write(fd, line, ret);
		free(line);
		line = NULL;
	}
	if (ret == -1 && line == NULL)
	{
		perror("hsh: getline");
		close(fd);
		shell->exit_status = 1;
		return (0);
	}
	close(fd);
	return (handle_in_redirection(shell, "shell_heredoc_buffer"));
}

/**
 * handle_redirections - handles the redirections accordingly
 * @shell : shell info
 * @cmd: command to be executed.
 * Return: 1 if no redirect_type found.
 */
int handle_redirections(Shell *shell, Command *cmd)
{
	switch (cmd->redirect_type)
	{
	case HSH_OP_REDIRECT_OUT:
	case HSH_OP_REDIRECT_OUT_CONCAT:
		return (handle_out_redirection(shell, cmd));
	case HSH_OP_REDIRECT_IN:
		return (handle_in_redirection(shell, cmd->redirect_to));
	case HSH_OP_REDIRECT_IN_HEREDOC:
		return (handle_heredoc(shell, cmd));
	case HSH_OP_REDIRECT_PIPE_OUT:
		return (handle_pipe(shell));
	default:
		return (1);
	}
	return (1);
}
