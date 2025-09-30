#include "../../../incls/prototypes.h"

int	ft_unset(t_command *cmd, t_env **env_list)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = 0;
	while (cmd->args[i])
	{
		if (!ft_isalpha(cmd->args[i][0]) && cmd->args[i][0] != '_')
		{
			printf("minishell: unset: '%s': not a valid identifier\n",
				cmd->args[i]);
			exit_status = 1;
		}
		else
			remove_env_node(env_list, cmd->args[i]);
		i++;
	}
	return (exit_status);
}
