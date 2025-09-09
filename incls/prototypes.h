#ifndef PROTOTYPES_H
# define PROTOTYPES_H

# include "minishell.h"
# include "structures.h"
# include "../libft/libft.h"

// Function prototypes in signal.c
t_sa		init_sigaction(void (*handler)(int));
void		handle_sigint(int sig);

// Function prototypes from memory_arena.c
void		*alloc_arena(t_arena *arena, size_t size);
int			init_arena(t_arena *arena, size_t size);
char		*arena_strdup(t_arena *arena, const char *str);
void		free_arena(t_arena *arena);

// Function prototypes from parsing.c
t_token		*parser(const char *line);

// Function prototypes from tokenizer.c
t_token		*tokenizer(const char *line, t_arena *arena);
const char	*find_token_end(const char *start);

#endif
