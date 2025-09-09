#include "../incls/prototypes.h"

int	main(int ac, char *av[])
{	
	t_sa		sa;
	char		*line;
	t_token		*token_list;
	t_command	*command_list;
	t_arena		arena;
	
	(void)ac;
	(void)av;
	sa = init_sigaction(NULL);
	run_minishel_loop();
	return (0);
}

void	run_minishell_loop(void)
{
	char		*line;
	t_token		*token_list;
	t_command	*command_list;
	t_arena		arena;

	while(1)
	{
		line = readline("my_prompt> ");
		if (line == NULL)
		{
			printf("exit\n");
			break ;
		}
		init_arena(&arena, (ft_strlen(line) * 2) + 1024);
		token_list = tokenizer(line, &arena);
		if (!token_list)
		{
			free(line);
			free_arena(&arena);
			continue ;
		}
		command_list = parse_commands(token_list, &arena);
		if (!command_list)
		{
			free(line);
			free_arena(&arena);
			continue ;
		}
		// execution part
		free(line);
		free_arena(&arena);
	}
}
