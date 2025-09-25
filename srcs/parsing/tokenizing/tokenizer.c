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
		printf("DEBUG C1-G: Token creation range. Cursor: %p, End: %p, Len: %zu\n", (void *)cursor, (void *)token_end, token_end - cursor);
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

	if (*start == '|' || *start == '<' || *start == '>')
	{
		if (*(start + 1) == *start)
			return (start + 2);
		return (start + 1);
	}
	if (*start == '\'' || *start == '"')
	{
		end = start + 1;
		while (*end && *end != *start)
			end++;
		if (!*end)
		{
			ft_putstr_fd("Error: unclosed quote\n", 2);
			return (NULL);
		}
		printf("DEBUG C1-F: Found quoted token. Start: %p, End: %p, Length: %zu\n", (void *)start, (void *)end, end + 1 - start);
		return (end + 1);
	}
	end = start;
	while (*end && *end != ' ' && *end != '\t' && *end != '|' && *end != '<'
		&& *end != '>')
		end++;
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
	else if (*cursor == '>')
		new->type = GREAT_TOKEN;
	else if (*cursor == '<')
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
