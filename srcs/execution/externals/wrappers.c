#include "../../../incls/prototypes.h"

void	execve_wrapper(t_command *cmd, t_env **env_list)
{
	char	*cmd_path;
	char	**envp;

	envp = env_list_to_array(*env_list);
	if (!envp)
		exit(1);
	cmd_path = cmd_check(cmd->args[0], env_list);
	if (!cmd_path)
	{
		handle_error(E_CMD_NOT_FOUND, cmd->args[0]);
		free_char_array(envp);
		exit(127);
	}
	execve(cmd_path, cmd->args, envp);
	free_char_array(envp);
	if (errno == EACCES)
	{
		handle_error(E_PERMISSION_DENIED, cmd->args[0]);
		exit(126);
	}
	else
	{
		handle_error(E_CMD_NOT_FOUND, cmd->args[0]);
		exit(127);
	}
}

void	free_char_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
