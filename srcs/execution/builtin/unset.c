#include "../../../incls/prototypes.h"

int	ft_unset(t_command *cmd, t_env **env_list)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = 0;
	while (cmd->args[i])
	{
		if (!is_valid_env_name(cmd->args[i]))
		{
			// printf("minishell: unset: '%s': not a valid identifier\n",
			// 	cmd->args[i]);
			exit_status = 0;
		}
		else
			remove_env_node(env_list, cmd->args[i]);
		i++;
	}
	return (exit_status);
}
