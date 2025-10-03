#include "../../incls/prototypes.h"

static t_arena_chunk	*allocate_new_chunk(t_arena *arena, size_t min_size);

int	init_arena(t_arena *arena, size_t initial_size)
{
	if (arena == NULL)
		return (-1);
	arena->head = NULL;
	arena->current = NULL;
	arena->chunk_size = ARENA_DEFAULT_CHUNK_SIZE;
	if (initial_size > arena->chunk_size)
		arena->chunk_size = initial_size;
	if (!allocate_new_chunk(arena, initial_size))
		return (-1);
	return (0);
}

void	*alloc_arena(t_arena *arena, size_t size)
{
	t_arena_chunk	*chunk;
	void			*ptr;

	if (arena == NULL || size == 0)
		return (NULL);
	chunk = arena->current;
	if (chunk->offset + size <= chunk->size)
	{
		ptr = chunk->buffer + chunk->offset;
		chunk->offset += size;
		return (ptr);
	}
	chunk = allocate_new_chunk(arena, size);
	if (!chunk)
		return (NULL);
	ptr = chunk->buffer + chunk->offset;
	chunk->offset += size;
	return (ptr);
}

char	*arena_strdup(t_arena *arena, const char *str)
{
	char	*new_str;
	size_t	len;

	if (str == NULL)
		return (NULL);
	len = ft_strlen(str) + 1;
	new_str = (char *)alloc_arena(arena, len);
	if (new_str)
		ft_memcpy(new_str, str, len);
	return (new_str);
}

void	free_arena(t_arena *arena)
{
	t_arena_chunk	*current_chunk;
	t_arena_chunk	*next_chunk;

	if (arena == NULL)
		return ;
	current_chunk = arena->head;
	while (current_chunk)
	{
		next_chunk = current_chunk->next;
		if (current_chunk->buffer)
			free(current_chunk->buffer);
		free(current_chunk);
		current_chunk = next_chunk;
	}
	arena->head = NULL;
	arena->current = NULL;
	arena->chunk_size = 0;
}

static t_arena_chunk	*allocate_new_chunk(t_arena *arena, size_t min_size)
{
	t_arena_chunk	*new_chunk;
	size_t			chunk_size;

	chunk_size = ARENA_DEFAULT_CHUNK_SIZE;
	if (min_size > chunk_size)
		chunk_size = min_size;
	new_chunk = (t_arena_chunk *)malloc(sizeof(t_arena_chunk));
	if (!new_chunk)
		return (NULL);
	new_chunk->buffer = (char *)malloc(chunk_size);
	if (!new_chunk->buffer)
	{
		free(new_chunk);
		return (NULL);
	}
	new_chunk->size = chunk_size;
	new_chunk->offset = 0;
	new_chunk->next = NULL;
	if (arena->current)
		arena->current->next = new_chunk;
	else
		arena->head = new_chunk;
	arena->current = new_chunk;
	return (new_chunk);
}
