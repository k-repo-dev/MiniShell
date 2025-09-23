#include "../../incls/prototypes.h"

t_env	*init_env_list(char **envp)
{
	t_env	*head;
	char	*equals_sign;

	head = NULL;
	while (*envp)
	{
		equals_sign = ft_strcr(*envp, '=');
		if (equals_sign)
			add_env_node(&head, ft_strndup(*envp, equals_sign - *envp), equals_sign + 1);
		else
			add_env_node(&head, ft_strdup(*envp), NULL);
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
