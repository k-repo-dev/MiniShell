#include "../../../incls/prototypes.h"

static int	is_valid_env_name(const char *name)
{
	int	i;

	i = 0;
	if (!name || !name[0])
		return (0);
	if (!(ft_isalpha(name[0]) || name[0] == '_'))
		return (0);
	while (name[i] && name[i] != '=')
	{
		if (!(ft_isalnum(name[i]) || name[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

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
		if (!is_valid_env_name(cmd->args[i]))
		{
			// printf("minishell: export: '%s': not a valid identifier\n",
			// 	cmd->args[i]);
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
	int		size;
	t_env	**array;
	int		i;

	i = 0;
	size = ft_listsize(env_list);
	if (size == 0)
		return ;
	array = stack_to_array(env_list, size);
	if (!array)
		return ;
	bubble_sort(array, size);
	while (i < size)
	{
		printf("declare -x %s", array[i]->key);
		if (array[i]->value)
			printf("=\"%s\"", array[i]->value);
		printf("\n");
		i++;
	}
	free(array);
}

void	bubble_sort(t_env **array, int size)
{
	int		i;
	int		j;
	t_env	*temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (strcmp(array[j]->key, array[j + 1]->key) > 0)
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}
