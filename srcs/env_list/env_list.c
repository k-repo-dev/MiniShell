#include "../../incls/prototypes.h"

t_env	*init_env_list(char **envp)
{
	t_env	*head;
	t_env	*current;
	t_env	*new_node;
	char	*equal_sign;

	head = NULL;
	current = NULL;
	while (*envp)
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (NULL);
		equal_sign = ft_strchr(*envp, '=');
		if (equal_sign)
		{
			new_node->key = ft_strndup(*envp, equal_sign - *envp);
			new_node->value = ft_strdup(equal_sign + 1);
		}
		else
		{
			new_node->key = ft_strdup(*envp);
			new_node->value = NULL;
		}
		new_node->next = NULL;
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
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
		head = head ->next;
		free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}
