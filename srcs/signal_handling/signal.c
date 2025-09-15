#include "../../incls/prototypes.h"

int	init_sigaction(void (*handler)(int))
{
	t_sa	sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		ft_putstr_fd("Error: sigaction", 2);
		return (-1);
	}
	return (0);
}

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
