#ifndef MEMORY_H
# define MEMORY_H

# include "minishell.h"

typedef struct	s_arena
{
	char	*buffer;
	size_t	size;
	size_t	offset;
}	t_arena;

// Function prototypes from memory_arena.c
int		memory_arena(const char *command_line);
void	*alloc_arena(t_arena *arena, size_t size);
int		init_arena(t_arena *arena, size_t size);
void	free_arena(t_arena *arena);

#endif
