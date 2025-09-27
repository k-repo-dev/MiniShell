#include "../../../incls/prototypes.h"

static t_token	*create_new_token(t_arena *arena, const char *cursor, const char *token_end);
static void		link_token(t_token **head, t_token **last, t_token *new);

t_token	*tokenizer(const char *line, t_arena *arena)
{
	t_token		*head;
	t_token		*last;
	t_token		*new;
	const char	*cursor;
	const char	*token_end;

	head = NULL;
	last = NULL;
	cursor = line;
	while (*cursor)
	{
		while (*cursor == ' ' || *cursor == '\t')
			cursor++;
		if (!*cursor)
			break ;
		token_end = find_token_end(cursor);
		if (!token_end)
			return (NULL);
		new = create_new_token(arena, cursor, token_end);
		if (!new)
			return (NULL);
		link_token(&head, &last, new);
		cursor = token_end;
	}
	return (head);
}

const char	*find_token_end(const char *start)
{
	const char	*end;
	char		quote_char;

	if (*start == '|' || *start == '<' || *start == '>')
	{
		if (*(start + 1) == *start)
			return (start + 2);
		return (start + 1);
	}
	end = start;
	while (1)
	{
		while (*end && *end != ' ' && *end != '\t' && *end != '|' && *end != '<'
				&& *end != '>' && *end != '\'' && *end != '"')
			end++;
		if (!*end || *end == ' ' || *end == '\t' || *end == '|' || *end == '<'
				|| *end == '>')
			return (end);
		if (*end == '\'' || *end == '"')
		{
			quote_char = *end;
			end++;
			while (*end && *end != quote_char)
				end++;
			if (!*end)
				return (NULL);
			end++;
			continue ;
		}
		break ;
	}
	return (end);
}

static t_token	*create_new_token(t_arena *arena, const char *cursor, const char *token_end)
{
	t_token	*new;

	new = (t_token *)alloc_arena(arena, sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = arena_strndup(arena, cursor, token_end - cursor);
	if (!new->value)
		return (NULL);
	new->next = NULL;
	if (ft_strcmp(new->value, ">>") == 0)
		new->type = APPEND_TOKEN;
	else if (ft_strcmp(new->value, "<<") == 0)
		new->type = HEREDOC_TOKEN;
	else if (ft_strcmp(new->value, "|") == 0)
		new->type = PIPE_TOKEN;
	else if (new->value[0] == '>')
		new->type = GREAT_TOKEN;
	else if (new->value[0] == '<')
		new->type = LESS_TOKEN;
	else
		new->type = ARG_TOKEN;
	return (new);
}

static void	link_token(t_token **head, t_token **last, t_token *new)
{
	if (!*head)
		*head = new;
	else
		(*last)->next = new;
	*last= new;
}
