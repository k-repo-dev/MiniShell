#include "../../incls/prototypes.h"

t_sa	init_sigaction(void (*handler)(int))
{
	t_sa	sa;

	(void)handler;
	return (sa);
}

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
