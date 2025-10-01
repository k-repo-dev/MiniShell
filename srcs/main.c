#include "../incls/prototypes.h"

static int	run_minishell_loop(t_env **env_list);

int	main(int ac, char *av[], char **envp)
{
	t_env	*env_list;
	int		exit_code;

	(void)ac;
	(void)av;
	if (init_sigaction(handle_sigint) == -1)
		return (1);
	env_list = init_env_list(envp);
	exit_code = run_minishell_loop(&env_list);
	if (env_list)
		free_env_list(env_list);
	return (exit_code);
}

static int	run_minishell_loop(t_env **env_list)
{
	char		*line;
	t_token		*token_list;
	t_command	*command_list;
	t_arena		arena;
	int			exit_status;
	int			final_exit_code;

	exit_status = 0;
	while (1)
	{
		ft_memset(&arena, 0, sizeof(t_arena));
		command_list = NULL;
		// if (isatty(fileno(stdin))) //<<<<<<<<<< minishell tester
		line = readline("my_prompt> ");
		// else
		// {
		// 	line = get_next_line(fileno(stdin));
		// 	line = ft_strtrim(line, "\n");
		// 	free(line);
		// }
		if (line == NULL)
		{
			// printf("exit\n"); // remove after
			rl_clear_history();
			if (command_list)
				cleanup_redirs(command_list);
			free_arena(&arena);
			free_env_list(*env_list);
			*env_list = NULL;
			return (exit_status);
		}
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		if (*line)
			add_history(line);
		init_arena(&arena, (ft_strlen(line) * 2) + 4096);
		token_list = tokenizer(line, &arena);
		if (token_list == NULL)
		{
			exit_status = handle_error(E_SYNTAX_ERROR, NULL);
			free(line);
			continue ;
		}
		command_list = parse_commands(token_list, &arena);
		if (command_list == NULL)
		{
			exit_status = handle_error(E_SYNTAX_ERROR, NULL);
			free(line);
			continue ;
		}
		expand_commands(command_list, &arena, exit_status, *env_list);
		exit_status = parent_loop(command_list, env_list, exit_status);
		if (exit_status == -1 || exit_status == -2)
		{
			if (exit_status == -2)
				final_exit_code = 2;
			else
			{
				if (command_list && command_list->args && command_list->args[1]
					&& is_numeric(command_list->args[1]))
					final_exit_code = (int)ft_atoi(command_list->args[1]);
				else
					final_exit_code = exit_status;
			}
			free(line);
			free_arena(&arena);
			rl_clear_history();
			free_env_list(*env_list);
			*env_list = NULL;
			return (final_exit_code);
		}
		free(line);
		free_arena(&arena);
	}
	return (exit_status);
}
