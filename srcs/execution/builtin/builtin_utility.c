#include "../../../incls/prototypes.h"

int	handle_builtins(t_command *cmd, t_env **env_list, int last_status)
{
	if (!cmd->args[0])
		return (0);
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (builtin_echo(cmd));
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (ft_cd(cmd, env_list));
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (ft_export(cmd, env_list));
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (ft_unset(cmd, env_list));
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (ft_env(*env_list));
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (ft_exit(cmd, last_status));
	return (handle_error(E_CMD_NOT_FOUND, cmd->args[0]));
}

t_env	**stack_to_array(t_env *env_list, int size)
{
	t_env	**array;
	int		i;

	i = 0;
	array = malloc(sizeof(t_env *) * size);
	if (!array)
		return (NULL);
	while (i < size)
	{
		array[i] = env_list;
		env_list = env_list->next;
		i++;
	}
	return (array);
}

int	ft_listsize(t_env *list)
{
	int	count;

	count = 0;
	while (list)
	{
		count++;
		list = list->next;
	}
	return (count);
}
