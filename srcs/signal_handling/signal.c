#include "../../incls/prototypes.h"

volatile sig_atomic_t g_signal_status = 0;

int	init_sigaction(void (*handler)(int))
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handler;
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (-1);
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (-1);
	return (0);
}

void	handle_sigint(int signum)
{
	if (signum == SIGINT)
	{
		g_signal_status = signum;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
