#include "../incls/minishell.h"

int	main(int ac, char *av[])
{	
	t_sa	sa;
	char	*line;
	
	(void)ac;
	(void)av;
	sa = init_sigaction(handle_sigint);
	while (1)
	{
		line = readline("my_prompt> ");
		if (line == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		input_parser(line);
		free(line);
	}
	return (0);
}


