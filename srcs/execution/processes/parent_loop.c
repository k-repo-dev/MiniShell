#include "../../../incls/prototypes.h"

int	parent_loop(t_command *cmd_list, t_env **env_list, int last_status)
{
	int	exit_status;

	if (cmd_list && (!cmd_list->args || !cmd_list->args[0]))
		return (handle_error(E_EMPTY_CMD, NULL));
	if (cmd_list && cmd_list->args && is_parent_builtin(cmd_list->args[0])
		&& cmd_list->next == NULL)
	{
		exit_status = handle_redirs(cmd_list->redirs);
		if (exit_status != 0)
		{
			cleanup_redirs(cmd_list);
			return (exit_status);
		}
		exit_status = handle_builtins(cmd_list, env_list, last_status);
		cleanup_redirs(cmd_list);
		return (exit_status);
	}
	else
	{
		// child loop
		exit_status = execute_pipeline(cmd_list, env_list);
		return (exit_status);
	}
}

int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	is_parent_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}
