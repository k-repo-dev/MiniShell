#include "../../../incls/prototypes.h"

static size_t	handle_single_quotes(const char *str, int *i);
static size_t	handle_env_var(const char *str, int *i, int exit_status, t_env *env_list);

size_t	get_expanded_len(const char *str, int exit_status, t_env *env_list)
{
	size_t	len;
	int		i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			len += handle_single_quotes(str, &i);
		else if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1]) 
				|| str[i + 1] == '?'))
			len += handle_env_var(str, &i, exit_status, env_list);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

static size_t	handle_single_quotes(const char *str, int *i)
{
	size_t	len;

	len = 1;
	(*i)++;
	while (str[*i] && str[*i] != '\'')
	{
		len++;
		i++;
	}
	if (str[*i] == '\'')
		len++;
	return (len);
}

static size_t	handle_env_var(const char *str, int *i, int exit_status, t_env *env_list)
{
	size_t	len;
	int		start;
	char	var_name[256];
	char	*value;

	len = 0;
	(*i)++;
	if (str[*i] == '?')
	{
		value = get_variable_value("?", exit_status, NULL);
		if (value)
			len += ft_strlen(value);
		if (value)
			free(value);
		(*i)++;
	}
	else
	{
		start = *i;
		while (str[*i] && ft_isalnum(str[*i]))
			(*i)++;
		ft_strlcpy(var_name, &str[start], (*i) - start + 1);
		value = get_env_value(env_list, var_name);
		if (value)
			len += ft_strlen(value);
	}
	return (len);
}

char	*get_variable_value(const char *var_name, int exit_status,
		t_arena *arena)
{
	const char	*value;

	if (var_name && var_name[0] == '?' && !var_name[1])
	{
		if (arena == NULL)
			return (ft_itoa(exit_status));
		return (arena_itoa(exit_status, arena));
	}
	value = getenv(var_name);
	if (!value)
		return (NULL);
	if (arena == NULL)
		return (ft_strdup(value));
	return (arena_strdup(arena, value));
}
