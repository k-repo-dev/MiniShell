#include "../../../incls/prototypes.h"

t_token	*create_new_token(t_arena *arena, const char *cursor, const char *token_end)
{
	t_token	*new_token;

	new_token = (t_token *)alloc_arena(arena, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = arena_strndup(arena, cursor, token_end - cursor);
	if (!new_token->value)
		return (NULL);
	new_token->next = NULL;
	set_token_type(new_token);
	return (new_token);
}

void	link_token(t_token **head, t_token **last, t_token *new_token)
{
	if (!*head)
		*head = new_token;
	else
		(*last)->next = new_token;
	*last = new_token;
}

void	set_token_type(t_token *new_token)
{
	if (ft_strcmp(new_token->value, ">>") == 0)
		new_token->type = APPEND_TOKEN;
	else if (ft_strcmp(new_token->value, "<<") == 0)
		new_token->type = HEREDOC_TOKEN;
	else if (ft_strcmp(new_token->value, "|") == 0)
		new_token->type = PIPE_TOKEN;
	else if (new_token->value[0] == '>')
		new_token->type = GREAT_TOKEN;
	else if (new_token->value[0] == '<')
		new_token->type = LESS_TOKEN;
	else
		new_token->type = ARG_TOKEN;
}
