#include "../../../incls/prototypes.h"

t_token	*tokenizer(const char *line, t_arena *arena)
{
	t_token		*head;
	t_token		*current;
	const char	*cursor;

	head = NULL;
	current = NULL;
	cursor = line;
	while (*cursor != '\0')
	{
		while (ft_iswhitespace(*cursor) == 1)
			cursor++;
		identify_token_type(*)
	}
}
