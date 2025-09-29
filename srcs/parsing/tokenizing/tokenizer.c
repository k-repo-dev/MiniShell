#include "../../../incls/prototypes.h"

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
	const char	*ret;

	if (*start == '|' || *start == '<' || *start == '>')
	{
		if (*(start + 1) == *start)
			return (start + 2);
		return (start + 1);
	}
	end = start;
	while (1)
	{
		while (*end && *end!= ' ' && *end != '\t' && *end != '|'
				&& *end != '<' && *end != '>' && *end != '\''
				&& *end != '"')
			end++;
		ret = check_token_char(&end, &quote_char);
		if (ret != NULL)
			return (ret);
	}
	return (end);
}

const char	*check_token_char(const char **end, char *quote_char)
{
	if (!**end || **end == ' ' || **end == '\t' || **end == '|' || **end == '<'
		|| **end == '>')
		return (*end);
	if (**end == '\'' || **end == '"')
	{
		*quote_char = **end;
		*end = *end + 1;
		while (**end && **end != *quote_char)
			*end = *end + 1;
		if (!**end)
			return (NULL);
		*end = *end + 1;
		return (NULL);
	}
	return (*end);
}
