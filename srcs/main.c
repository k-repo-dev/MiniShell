#include "../incls/prototypes.h"

static int	run_minishell_loop(void);

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
	return (run_minishell_loop());
}

static int	run_minishell_loop(void)
{
	char		*line;
	t_token		*token_list;
	t_command	*command_list;
	t_arena		arena;
	int			exit_status;

	exit_status = 0;
	while(1)
	{
		line = readline("my_prompt> ");
		if (line == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		init_arena(&arena, (ft_strlen(line) * 2) + 1024);
		token_list = tokenizer(line, &arena);
		if (token_list)
		{
			command_list = parse_command(token_list, &arena);
			if (command_list)
			{
				expand_command(command_list, &arena, exit_status);
				// Execution starts here
			}
		}
		free(line);
		free_arena(&arena);
	}
	return (0);
}
