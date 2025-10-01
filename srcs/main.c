#include "../incls/prototypes.h"

static int	run_minishell_loop(t_env **env_list);
static int	process_input(t_env **env_list, int *exit_status);
static int	execute_line_logic(t_env **env_list, char **line, int *exit_status);
static int	handle_exit_command(t_command *cmd_list, int exit_status,
				int *final_exit_code);

int	main(int ac, char *av[], char **envp)
{
	t_env	*env_list;
	int		exit_code;

	(void)ac;
	(void)av;
	if (init_sigaction(handle_sigint) == -1)
		return (1);
	env_list = init_env_list(envp);
	printf("init_env_list done\n");
	exit_code = run_minishell_loop(&env_list);
	printf("run_minishell_loop done, now freeing the env_list\n");
	if (env_list)
		free_env_list(env_list);
	printf("bye-bye\n");
	return (exit_code);
}

static int	run_minishell_loop(t_env **env_list)
{
	int	exit_status;
	int	final_exit_code;

	exit_status = 0;
	while (1)
	{
		final_exit_code = process_input(env_list, &exit_status);
		if (final_exit_code != -1)
			return (final_exit_code);
		printf("process_input run correctly\n");
	}
}

static int	process_input(t_env **env_list, int *exit_status)
{
	char	*line;
	int		command_result;

	line = readline("my_prompt> ");
	if (line == NULL)
	{
		printf("exit\n");
		rl_clear_history();
		return (*exit_status);
	}
	if (*line == '\0')
	{
		free(line);
		return (-1);
	}
	if (*line)
		add_history(line);
	command_result = execute_line_logic(env_list, &line, exit_status);
	free(line);
	if (command_result != -1)
		return (command_result);
	return (-1);
}

static int	execute_line_logic(t_env **env_list, char **line, int *exit_status)
{
	t_arena		arena;
	t_token		*token_list;
	t_command	*cmd_list;
	int			command_status;
	int			final_exit_code_signal;

	ft_memset(&arena, 0, sizeof(t_arena));
	init_arena(&arena, (ft_strlen(*line) * 2) + 4096);
	token_list = tokenizer(*line, &arena);
	if (token_list == NULL)
	{
		free_arena(&arena);
		return (handle_error(E_SYNTAX_ERROR, NULL));
	}
	cmd_list = parse_commands(token_list, &arena);
	if (cmd_list == NULL)
	{
		free_arena(&arena);
		return (handle_error(E_SYNTAX_ERROR, NULL));
	}
	expand_commands(cmd_list, &arena, *exit_status, *env_list);
	command_status = parent_loop(cmd_list, env_list, *exit_status);
	final_exit_code_signal = -1;
	handle_exit_command(cmd_list, command_status, &final_exit_code_signal);
	free_arena(&arena);
	if (final_exit_code_signal != -1)
		return (final_exit_code_signal);
	*exit_status = command_status;
	return (-1);
}

static int	handle_exit_command(t_command *cmd_list, int exit_status,
		int *final_exit_code)
{
	t_command	*cmd;

	*final_exit_code = -1;
	cmd = cmd_list;
	if (cmd && cmd->args && cmd->args[0] && ft_strcmp(cmd->args[0],
			"exit") == 0)
	{
		if (exit_status == -1)
		{
			if (cmd->args[1] && is_numeric(cmd->args[1]))
				*final_exit_code = (int)ft_atoi(cmd->args[1]) & 0xFF;
			else
				*final_exit_code = 0;
			rl_clear_history();
			return (1);
		}
	}
	else if (exit_status == 2)
	{
		*final_exit_code = 2;
		return (1);
	}
	return (0);
}
