#include "../../incls/prototypes.h"

t_token	*parser(const char *line)
{
	t_arena	arena;
	t_token	*token_head;
	size_t	arena_size;

	arena_size = (ft_strlen(line) * 2) + 1024;
	if (init_arena(&arena, arena_size) != 0)
		return (NULL);
	token_head = tokenizer(line, &arena);
	return (token_head);
}
