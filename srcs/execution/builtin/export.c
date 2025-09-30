#include "../../../incls/prototypes.h"

int	ft_export(t_command *cmd, t_env **env_list)
{
	int		i;
	char	*equals_sign;
	int		exit_status;
	char	*arg_copy;

	i = 1;
	exit_status = 0;
	if (!cmd->args[i])
	{
		print_exported_env(*env_list);
		return (0);
	}
	while (cmd->args[i])
	{
		arg_copy = ft_strdup(cmd->args[i]);
		if (!arg_copy)
			return (1);
		equals_sign = ft_strchr(cmd->args[i], '=');
		if (!ft_isalpha(arg_copy[0]) && arg_copy[0] != '_')
		{
			printf("minishell: export: '%s': not a valid identifier\n",
				cmd->args[i]);
			exit_status = 1;
		}
		else if (!equals_sign)
		{
			if (get_env_value(*env_list, cmd->args[i]) == NULL)
				add_env_node(env_list, cmd->args[i], NULL);
		}
		else
		{
			*equals_sign = '\0';
			add_env_node(env_list, arg_copy, equals_sign + 1);
		}
		free(arg_copy);
		i++;
	}
	return (exit_status);
}

void	print_exported_env(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		printf("declare -x %s", current->key);
		if (current->value)
			printf("=\"%s\"", current->value);
		printf("\n");
		current = current->next;
	}
}

void	export_sort(void);