#include "../../incls/prototypes.h"

static char		*extract_key(char *env_str, char **equals_sign);
static void		update_existing_node(t_env *node, const char *value_source,
								 char *key_to_transfer);
static t_env	*create_new_node(char *key_to_transfer, const char *value_source);
static void		add_env_node_transfer_key(t_env **env_list, char *key_to_transfer,
									   const char *value_source);

t_env	*init_env_list(char **envp)
{
	t_env	*head;
	char	*equals_sign;
	char	*key_to_transfer;

	head = NULL;
	equals_sign = NULL;
	key_to_transfer = NULL;
	while (*envp)
	{
		key_to_transfer = extract_key(*envp, &equals_sign);
		if (equals_sign)
			add_env_node_transfer_key(&head, key_to_transfer, equals_sign);
		else
			add_env_node_transfer_key(&head, key_to_transfer, NULL);
		envp++;
	}
	return (head);
}

static char	*extract_key(char *env_str, char **equals_sign)
{
	char	*key;

	key = NULL;
	*equals_sign = ft_strchr(env_str, '=');
	if (*equals_sign)
		key = ft_strndup(env_str, *equals_sign - env_str);
	else
		key = ft_strdup(env_str);
	return (key);
}

static void	add_env_node_transfer_key(t_env **env_list, char *key_to_transfer,
									  const char *value_source)
{
	t_env	*node;

	node = find_env_node(*env_list, key_to_transfer);
	if (node)
		update_existing_node(node, value_source, key_to_transfer);
	else
	{
		node = create_new_node(key_to_transfer, value_source);
		if (!node)
			return ;
		node->next = *env_list;
		*env_list = node;
	}
}

static void	update_existing_node(t_env *node, const char *value_source, char *key_to_transfer)
{
	free(node->value);
	if (value_source)
		node->value = ft_strdup(value_source);
	else
		node->value = NULL;
	free(key_to_transfer);
}

static t_env	*create_new_node(char *key_to_transfer, const char *value_source)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
	{
		free(key_to_transfer);
		return (NULL);
	}
	node->key = key_to_transfer;
	node->value = NULL;
	if (value_source)
		node->value = ft_strdup(value_source);
	return (node);
}
