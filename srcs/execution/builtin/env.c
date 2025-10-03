#include "../../../incls/prototypes.h"

// int	ft_env(t_env *env_list)
// {
// 	while (env_list)
// 	{
// 		printf("%s=%s\n", env_list->key, env_list->value);
// 		env_list = env_list->next;
// 	}
// 	return (0);
// }

int	ft_env(t_command *cmd, t_env *env_list)
{
	if (cmd->args[1])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	while (env_list)
	{
		if (env_list->value)
		{
			printf("%s=%s\n", env_list->key, env_list->value);
		}
		env_list = env_list->next;
	}
	return (0);
}
