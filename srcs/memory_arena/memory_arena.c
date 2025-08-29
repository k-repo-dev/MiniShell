#include "../../incls/minishell.h"
#include "../../incls/memory.h"

int	memory_arena(const char *command_line)
{
	t_arena	arena;

	
}

int	init_arena(t_arena *arena, size_t size)
{
	if (arena == NULL || size == 0)
	{
		//ft_putstr_fd(ARENA_ERR, 2);
		return (-1);
	}
	arena->buffer = (char *)malloc(size);
	if (arena->buffer == NULL)
	{
		//ft_putstr_fd(ALLOC_ERR, 2);
		return (-1);
	}
	arena->size = size;
	arena->offset = 0;
	return (0);
}

void	*alloc_arena(t_arena *arena, size_t size)
{
	void	*ptr;

	if (arena->offset + size > arena->size)
		return (NULL);
	ptr = arena->buffer + arena->offset;
	arena->offset += size;
	return (ptr);
}

void	free_arena(t_arena *arena)
{
	if (arena && arena->buffer)
	{
		free(arena->buffer);
		arena->buffer = NULL;
		arena->size = 0;
		arena->offset = 0;
	}
}
