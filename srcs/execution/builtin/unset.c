#include "../../../incls/prototypes.h"

int	ft_unset(t_command *cmd, t_env **env_list)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		if (is_valid_env_name(cmd->args[i]))
			remove_env_node(env_list, cmd->args[i]);
		i++;
	}
	return (0);
}
