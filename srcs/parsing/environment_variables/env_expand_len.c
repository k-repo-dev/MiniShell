#include "../../../incls/prototypes.h"

static size_t	handle_single_quotes(const char *str, int *i);
static size_t	handle_env_var(const char *str, int *i, int exit_status, t_env *env_list);
static size_t	handle_exit_status_var(int *i, int exit_status);
static size_t	handle_normal_env_var(const char *str, int *i, t_env *env_list);

size_t	get_expand_len(const char *str, int exit_status, t_env *env_list)
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
	char	quote_char;

	len = 0;
	quote_char = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote_char)
	{
		len++;
		(*i)++;
	}
	len += 2;
	if (str[*i] == quote_char)
		(*i)++;
	return (len);
}

static size_t	handle_env_var(const char *str, int *i, int exit_status, t_env *env_list)
{
	size_t	len;

	len = 0;
	(*i)++;
	if (str[*i] == '?')
		len += handle_exit_status_var(i, exit_status);
	else
		len = handle_normal_env_var(str, i, env_list);
	return (len);
}

static size_t	handle_exit_status_var(int *i, int exit_status)
{
	char	*value;
	size_t	len;

	value = get_variable_value("?", exit_status, NULL);
	len = 0;
	if (value)
	{
		len += ft_strlen(value);
		free(value);
	}
	(*i)++;
	return (len);
}

static size_t	handle_normal_env_var(const char *str, int *i, t_env *env_list)
{
	char	var_name[256];
	char	*value;
	int		start;
	size_t	len;

	start = *i;
	value = NULL;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	ft_strlcpy(var_name, &str[start], (*i) - start + 1);
	value = get_env_value(env_list, var_name);
	len = 0;
	if (value)
		len = ft_strlen(value);
	return (len);
}
