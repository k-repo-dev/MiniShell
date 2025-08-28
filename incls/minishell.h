#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef struct sigaction	t_sa;

// Funcction prototypes in signal.c
t_sa	init_sigaction(void (*handler)(int, siginfo_t *, void *));
void	handle_sigint(int sig);

#endif
