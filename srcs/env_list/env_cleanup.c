#include "../../incls/prototypes.h"

void	free_env_list(t_env *head)
{
	t_env	*current;
	t_env	*tmp;

	current = head;
	tmp = NULL;
	while (current)
	{
		tmp = current->next;
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = tmp;
	}
}
