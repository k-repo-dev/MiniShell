#include "../../incls/prototypes.h"

static t_env	*create_new_node_manip(const char *key, const char *value);

void	add_env_node(t_env **env_list, const char *key, const char *value)
{
	t_env	*node;

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
		node = create_new_node_manip(key, value);
		if (!node)
			return ;
		node->next = *env_list;
		*env_list = node;
	}
}

static t_env	*create_new_node_manip(const char *key, const char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->value = NULL;
	if (value)
		node->value = ft_strdup(value);
	return (node);
}

t_env	*find_env_node(t_env *env_list, const char *key)
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
