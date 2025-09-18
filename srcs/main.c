#include "../incls/prototypes.h"

static int	run_minishell_loop(char **envp);

int	main(int ac, char *av[], char **envp)
{
	(void)ac;
	(void)av;
	if (init_sigaction(handle_sigint) == -1)
		return (1);
	return (run_minishell_loop(envp));
}

static int	run_minishell_loop(char **envp)
{
	char		*line;
	t_token		*token_list;
	t_command	*command_list;
	t_arena		arena;
	int			exit_status;

	exit_status = 0;
	while (1)
	{
		line = readline("my_prompt> ");
		if (line == NULL)
		{
			printf("\n###Exit Read###\n");
			break ;
		}
		if (*line)
			add_history(line);
		init_arena(&arena, (ft_strlen(line) * 2) + 1024);
		token_list = tokenizer(line, &arena);
		if (token_list)
		{
			command_list = parse_commands(token_list, &arena);
			if (command_list)
			{
				expand_commands(command_list, &arena, exit_status);
				parent_loop(&command_list, envp); // Execution starts here
			}
		}
		free(line);
		free_arena(&arena);
	}
	return (0);
}
