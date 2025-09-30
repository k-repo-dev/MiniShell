#include "../../incls/prototypes.h"

static int	count_env_nodes(t_env *head);
static char	*create_combined_str(t_env *node);
static void	cleanup_array(char **env_array, int count);

char	**env_list_to_array(t_env *head)
{
	char	**env_array;
	t_env	*current;
	int		count;
	int		i;

	count = count_env_nodes(head);
	current = head;
	i = 0;
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	while (current)
	{
		env_array[i] = create_combined_str(current);
		if (!env_array)
		{
			cleanup_array(env_array, i);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

static int	count_env_nodes(t_env *head)
{
	int	count;

	count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}

static char	*create_combined_str(t_env *node)
{
	size_t	total_len;
	char	*combined_str;

	total_len = ft_strlen(node->key) + ft_strlen(node->value) + 2;
	combined_str = malloc(total_len);
	if (!combined_str)
		return (NULL);
	ft_strlcpy(combined_str, node->key, total_len);
	ft_strlcat(combined_str, "=", total_len);
	ft_strlcat(combined_str, node->value, total_len);
	return (combined_str);
}

static void	cleanup_array(char **env_array, int count)
{
	while (count >= 0)
	{
		count--;
	}
	free(env_array);
}
