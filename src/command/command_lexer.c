#include "hsh.h"

static token_t s_tokens[] = {
	{"&&", 2, HSH_OP_AND},         {"||", 2, HSH_OP_OR},
	{";", 1, HSH_OP_NONE},         {"\n", 1, HSH_OP_NONE},
	{"|", 1, HSH_OP_PIPE},         {">>", 2, HSH_OP_REDIRECT_OUT_CONCAT},
	{">", 1, HSH_OP_REDIRECT_OUT}, {"<<", 2, HSH_OP_REDIRECT_IN_HEREDOC},
	{"<", 1, HSH_OP_REDIRECT_IN},  {NULL, 0, HSH_OP_NONE}
};


/**
 * get_str - skips the spaces and tabs
 * @str : string
 * Return: the pointer to the string with blanks skipped
 */
char *get_str(char *str)
{
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	return (str);
}

/**
 * skip_tokens - skips the token
 * @str : string
 * Return: the pointer to the string till the token appears
 */
char *skip_tokens(char *str)
{
	char *delims = "\n><|;& ";

	while (*str && (_strchr(delims, *str) == NULL))
	{
		str++;
	}
	return (str);
}

/**
 * fetch_token - fetches the token in a string
 * @str : string
 * Return: the token in a string.
 */
token_t *fetch_token(char *str)
{
	token_t *tokens = s_tokens;

	while (tokens->token && (_strncmp(str, tokens->token, tokens->len) != 0))
	{
		tokens++;
	}
	return (tokens);
}
/**
 * process_token - Lexes the user input
 * @shell : shell info
 * @cmd: command list
 * @token: token
 * @start: start of the string
 * @paramCount: count of the args to the command
 * @status: 0 on syntax error
 * Return: end of the string after the token has been processed.
 */
char *process_token(Shell *shell, Command **cmd, token_t *token, char *start,
		    int *paramCount, int *status)
{
	char *end = start + token->len;

	if (cmd && (*cmd)->args[0] == NULL) /*syntax error like - '&& echo rose'*/
	{
		free_commands(*cmd);
		print_error(shell, token->token, NULL, HSH_SYNTAX_ERROR);
		*status = HSH_FAILURE;
		return (NULL);
	}
	else
	{
		switch (token->id)
		{
		case HSH_OP_PIPE:
			(*cmd)->redirect_type = HSH_OP_REDIRECT_PIPE_OUT;
		case HSH_OP_OR:
		case HSH_OP_AND:
		case HSH_OP_NONE:
			(*cmd)->op = token->id;
			*paramCount = 0;
			command_init(cmd);
			while ((*cmd) && (*cmd)->next != NULL)
				(*cmd) = (*cmd)->next;
			if (token->id == HSH_OP_PIPE)
				(*cmd)->redirect_type = HSH_OP_REDIRECT_PIPE_IN;
			break;
		case HSH_OP_REDIRECT_OUT:
		case HSH_OP_REDIRECT_OUT_CONCAT:
		case HSH_OP_REDIRECT_IN:
		case HSH_OP_REDIRECT_IN_HEREDOC:
			(*cmd)->redirect_type = token->id;
			break;
		}
	}
	return (end);
}

/**
 * lexer_run - Lexes the user input
 * @shell : shell info
 * @cmd_list: command list.
 */
void lexer_run(Shell *shell, Command **cmd_list)
{
	Command *cmd = NULL, *prev = NULL;
	char *start, *end, *line = shell->cmdLine;
	token_t *token;
	int paramCount = 0, status = HSH_SUCCESS;

	command_init(&cmd);
	prev = cmd;
	while (line && *line)
	{
		start = get_str(line);
		token = fetch_token(start);
		if (token->token)
			end = process_token(shell, &prev, token, start, &paramCount, &status);
		else
		{
			end = skip_tokens(start);
			while (prev && prev->next != NULL)
				prev = prev->next;
			if (end - start > 0)
			{
				if (!prev->redirect_to &&
				    (prev->redirect_type == HSH_OP_REDIRECT_OUT ||
				     prev->redirect_type == HSH_OP_REDIRECT_IN ||
				     prev->redirect_type == HSH_OP_REDIRECT_OUT_CONCAT ||
				     prev->redirect_type == HSH_OP_REDIRECT_IN_HEREDOC))
					prev->redirect_to = _strndup(start, end - start);
				else
				{
					prev->args[paramCount] = _strndup(start, end - start);
					paramCount++;
				}
			}
			else if (*end)
				end++;
		}
		line = end;
	}
	*cmd_list =  (status == HSH_SUCCESS) ? cmd : NULL;
}
