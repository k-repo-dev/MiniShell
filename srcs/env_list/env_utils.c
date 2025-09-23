#include "../../incls/prototypes.h"

int	add_env_node(t_env **head, const char *key, const char *value)
{
	t_env	*current;
	t_env	*new_node;

	current = *head;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (current->value)
				free(current->value);
			current->value = ft_strdup(value);
			return (0);
		}
		current = current->next;
	}
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (-1);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = *head;
	*head = new_node;
	return (0);
}

void	remove_env_node(t_env **head, const char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *head;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*head = current->next;
			free(current->key);
			if (current->value)
				free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

char	**env_list_to_array(t_env *head, t_arena *arena)
{
	char	**env_array;
	t_env	*current;
	int		count;
	int		i;

	count = 0;
	current = head;
	while (current)
	{
		count++;
		current = current->next;
	}
	env_array = alloc_arena(arena, sizeof(char *) * (count + 1));
	i = 0;
	current = head;
	while (current)
	{
		if (current->next)
		{
			size_t	total_len = ft_strlen(current->key) + ft_strlen(current->value) + 2;
			char	*combined_str = alloc_arena(arena, total_len);
			ft_strlcpy(combined_str, current->value, ft_strlen(current->key) + 1);
			ft_strlcat(combined_str, current->key, ft_strlen(current->key) + 1);
			ft_strlcat(combined_str, current->value, total_len);
			env_array[i] = combined_str;
		}
		else
			env_array[i] = arena_strdup(arena, current->key);
		current = current->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

char	*get_env_value(const char *key, t_env *env_list)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}
