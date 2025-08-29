#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef enum	e_token_type
{
	CMD,
	ARG,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT
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

#endif
