#include "../../../incls/prototypes.h"

static char	*get_token_value(t_token *token);
static int	is_operator(t_token *token);

int	check_syntax(t_token	*token_head)
{
	t_token	*current;

	current = token_head;
	if (!current)
		return (0);
	if (current->type == PIPE_TOKEN)
	{
		handle_error(E_SYNTAX_ERROR, get_token_value(current));
		return (1);
	}
	while (current)
	{
		if (is_operator(current) && current->next && is_operator(current->next))
		{
			if (current->type == PIPE_TOKEN && current->next->type == PIPE_TOKEN)
			{
				handle_error(E_SYNTAX_ERROR, get_token_value(current->next));
				return (1);
			}
			else if (current->type != PIPE_TOKEN)
			{
				handle_error(E_SYNTAX_ERROR, get_token_value(current->next));
				return (1);
			}
		}
		if (is_operator(current) && current->next == NULL)
		{
			handle_error(E_SYNTAX_ERROR, "newline");
			return (1);
		}
		current = current->next;
	}
	return (0);
}

static char	*get_token_value(t_token *token)
{
	if (token->type == PIPE_TOKEN)
		return ("|");
	if (token->type == LESS_TOKEN)
		return ("<");
	if (token->type == GREAT_TOKEN)
		return (">");
	if (token->type == HEREDOC_TOKEN)
		return ("<<");
	if (token->type == APPEND_TOKEN)
		return (">>");
	return (token->value);
}

static int	is_operator(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == PIPE_TOKEN || token->type == LESS_TOKEN
			|| token->type == GREAT_TOKEN || token->type == HEREDOC_TOKEN
			|| token->type == APPEND_TOKEN);
}
