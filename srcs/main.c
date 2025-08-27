#include "../incls/minishell.h"

int	main(int ac, char *av[])
{
	char *line;
	
	(void)ac;
	(void)av;
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
		free(line);
	}
	return (0);
}
