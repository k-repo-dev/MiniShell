#ifndef PROTOTYPES_H
# define PROTOTYPES_H

# include "../libft/libft.h"
# include "execution.h"
# include "minishell.h"
# include "structures.h"

// Function prototypes in signal.c
t_sa		init_sigaction(void (*handler)(int));
void		handle_sigint(int sig);

// Function prototypes from memory_arena.c
void		*alloc_arena(t_arena *arena, size_t size);
int			init_arena(t_arena *arena, size_t size);
char		*arena_strdup(t_arena *arena, const char *str);
void		free_arena(t_arena *arena);
char		*arena_itoa(int n, t_arena *arena);

// Function prortypes from memory_utils.c
size_t		ft_counter(long long n);

// Function prototypes from tokenizer.c
t_token		*tokenizer(const char *line, t_arena *arena);
const char	*find_token_end(const char *start);

// Function prototypes from commands.c
t_command	*parse_commands(t_token *token_head, t_arena *arena);

// Function prortypes from env_vars.c
void		expand_commands(t_command *cmd_list, t_arena *arena,
				int exit_status);

#endif
