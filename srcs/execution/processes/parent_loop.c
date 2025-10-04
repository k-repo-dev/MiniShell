#include "../../../incls/prototypes.h"

static int	execute_null_command(t_command *cmd);

int	parent_loop(t_command *cmd_list, t_env **env_list, int last_status)
{
	int	exit_status;

	if (cmd_list && (!cmd_list->args || !cmd_list->args[0]))
	{
		if (cmd_list->redirs)
			return (execute_null_command(cmd_list));
		return (handle_error(E_EMPTY_CMD, NULL));
	}
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

static int	execute_null_command(t_command *cmd)
{
	int	exit_status;
	int	original_stdout;
	int	original_stdin;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	if (original_stdin == -1 || original_stdout == -1)
	{
		cleanup_redirs(cmd);
		return (1);
	}
	exit_status = handle_redirs(cmd->redirs);
	cleanup_redirs(cmd);
	if (dup2(original_stdin, STDIN_FILENO) == -1 || dup2(original_stdout, STDOUT_FILENO) == -1)
	{
		close(original_stdin);
		close(original_stdout);
		return (1);
	}
	close(original_stdin);
	close(original_stdout);
	if (exit_status == 0)
		return (0);
	return (exit_status);
}
