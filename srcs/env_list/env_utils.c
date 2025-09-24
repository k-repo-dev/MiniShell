#include "../../incls/prototypes.h"

static t_env	*find_env_node(t_env *env_list, const char *key);

void	add_env_node(t_env **env_list, const char *key, const char *value)
{
	t_env	*node;
	char	*new_key;
	char	*new_value;

	node = find_env_node(*env_list, key);
	if (node)
	{
		free(node->value);
		if (value)
			node->value = ft_strdup(value);
		else
			node->value = NULL;
	}
	else
	{
		node = malloc(sizeof(t_env));
		if (!node)
			return ;
		new_key = ft_strdup(key);
		new_value = NULL;
		if (value)
			new_value = ft_strdup(value);
		node->key = new_key;
		node->value = new_value;
		node->next = *env_list;
		*env_list = node;
	}
}

static t_env	*find_env_node(t_env *env_list, const char *key)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
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
	size_t	total_len;
	char	*combined_str;

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
			total_len = ft_strlen(current->key) + ft_strlen(current->value) + 2;
			combined_str = alloc_arena(arena, total_len);
			ft_strlcpy(combined_str, current->value, ft_strlen(current->key)
				+ 1);
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

char	*get_env_value(t_env *env_list, const char *key)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}
