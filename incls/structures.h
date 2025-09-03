#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "minishell.h"

typedef struct sigaction	t_sa;

typedef enum	e_token_type
{
	CMD_TOKEN,
	ARG_TOKEN,
	PIPE_TOKEN,
	REDIRECT_IN_TOKEN,
	REDIRECT_OUT_TOKEN
}	t_token_type;

typedef struct	s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct	s_command
{
	char				**args;
	int					input_fd;
	int					output_fd;
	struct s_command	*next;
}	t_command;

typedef struct	s_arena
{
	char	*buffer;
	size_t	size;
	size_t	offset;
}	t_arena;

#endif
