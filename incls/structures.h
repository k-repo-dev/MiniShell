#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "minishell.h"

typedef struct sigaction	t_sa;

typedef struct s_signal
{
	volatile sig_atomic_t	signal_received;
}							t_signal;

typedef enum e_token_type
{
	CMD_TOKEN,
	ARG_TOKEN,
	PIPE_TOKEN,
	LESS_TOKEN,
	GREAT_TOKEN,
	HEREDOC_TOKEN,
	APPEND_TOKEN
}							t_token_type;

typedef struct s_token
{
	char					*value;
	t_token_type			type;
	struct s_token			*next;
}							t_token;

typedef struct s_redir
{
	t_token_type			type;
	char					*filename;
	struct s_redir			*next;
}							t_redir;

typedef struct s_command
{
	char					**args;
	t_redir					*redirs;
	struct s_command		*next;
}							t_command;

typedef struct s_arena
{
	char					*buffer;
	size_t					size;
	size_t					offset;
}							t_arena;

typedef struct s_env
{
	char					*key;
	char					*value;
	struct s_env			*next;
}							t_env;

#endif
