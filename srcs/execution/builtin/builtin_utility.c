#include "execution.h"

// Builtin brains
bool	is_builtin(const char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (true);
	else
		return (false);
}

void	exec_builtin(t_command **command_list, char **envp)
{
	t_command	*cmd;

	cmd = *command_list;
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		builtin_echo(cmd);
	// cd parent only
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		builtin_cd(cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		exit(1);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		builtin_env(envp);
	// else if (ft_strcmp(cmd->args[0], "unset") == 0)
	// 	builtin_unset(cmd, envp);
	// else if (ft_strcmp(cmd, "export") == 0)
	// 	builtin_export(cmd, envp);
}
