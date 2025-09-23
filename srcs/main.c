#include "../incls/prototypes.h"

static int	run_minishell_loop(t_env **env_list);

int	main(int ac, char *av[], char **envp)
{
	t_env	*env_list;

	(void)ac;
	(void)av;
	if (init_sigaction(handle_sigint) == -1)
		return (1);
	env_list = init_env_list(envp);
	return (run_minishell_loop(&env_list));
}

static int	run_minishell_loop(t_env **env_list)
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
				//expand_commands(command_list, &arena, exit_status);
				expand_commands(command_list, &arena, exit_status, *env_list);
				//parent_loop(&command_list, envp); // Execution starts here
				exit_status = parent_loop(command_list, env_list, exit_status);
			}
		}
		free(line);
		free_arena(&arena);
	}
	free_env_list(*env_list);
	return (0);
}
