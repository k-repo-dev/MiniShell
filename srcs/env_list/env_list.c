#include "../../incls/prototypes.h"

static void	add_env_node_transfer_key(t_env **env_list, char *key_to_transfer, const char *value_source);

t_env	*init_env_list(char **envp)
{
	t_env	*head;
	char	*equals_sign;
	char	*key_to_transfer;

	head = NULL;
	while (*envp)
	{
		equals_sign = ft_strchr(*envp, '=');
		if (equals_sign)
			key_to_transfer = ft_strndup(*envp, equals_sign - *envp);
		else
			key_to_transfer = ft_strdup(*envp);
		if (equals_sign)
			add_env_node_transfer_key(&head, key_to_transfer, equals_sign + 1);
		else
			add_env_node_transfer_key(&head, key_to_transfer, NULL);
		envp++;
	}
	return (head);
}

void	free_env_list(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

static void	add_env_node_transfer_key(t_env **env_list, char *key_to_transfer, const char *value_source)
{
	t_env	*node;

	node = find_env_node(*env_list, key_to_transfer);
	if (node)
	{
		free(node->value);
		if (value_source)
			node->value = ft_strdup(value_source);
		else
			node->value = NULL;
		free(key_to_transfer);
	}
	else
	{
		node = malloc(sizeof(t_env));
		if (!node)
		{
			free(key_to_transfer);
			return ;
		}
		node->key = key_to_transfer;
		node->value = NULL;
		if (value_source)
			node->value = ft_strdup(value_source);
		node->next = *env_list;
		*env_list = node;
	}
}
