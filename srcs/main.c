#include "../incls/prototypes.h"

int	main(int ac, char *av[])
{	
	t_sa	sa;
	char	*line;
	t_token	*tokens;
	
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
		tokens = parser(line);
		if (tokens)
		{
			//executions starts
		}
		free(line);
	}
	return (0);
}


