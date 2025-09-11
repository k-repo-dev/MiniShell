#include "../../../incls/prototypes.h"

static char		*expand_str(const char *str, int exit_status, t_arena *arena);
static size_t	get_expanded_len(const char *str, int exit_status);
static char		*copy_expanded_str(const char *str, int exit_status, t_arena *arena);
static char		*get_variable_value(const char *var_name, int exit_status, t_arena *arena);

void	expand_commands(t_command *cmd_list, t_arena *arena, int exit_status)
{
	t_command	*current_cmd;
	char		**tmp_args;

	current_cmd = cmd_list;
	while (current_cmd)
	{
		tmp_args = current_cmd->args;
		while (tmp_args && *tmp_args)
		{
			*tmp_args = copy_expanded_str(*tmp_args, exit_status, arena);
			tmp_args++;
		}
		current_cmd = current_cmd->next;
	}
}

static size_t	get_expanded_len(const char *str, int exit_status)
{
	size_t	len;
	int		i;
	int		start;
	char	*value;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			len++;
			i++;
			while (str[i] && str[i] != '\'')
			{
				len++;
				i++;
			}
			if (str[i] == '\'')
				len++;
		}
		else if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1]) || str[i + 1] == '?'))
		{
			i++;
			if (str[i] == '?')
			{
				value = get_variable_value("?", exit_status, NULL);
				if (value)
					len += ft_strlen(value);
				i++;
			}
			else
			{
				start = i;
				while (str[i] && ft_isalnum(str[i]))
					i++;
				char	var_name[i - start + 1];
				ft_strlcpy(var_name, &str[start], i - start + 1);
				value = get_variable_value(var_name, exit_status, NULL);
				if (value)
					len += ft_strlen(value);
			}
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

static char	*copy_expanded_str(const char *str, int exit_status, t_arena *arena)
{
	size_t		i;
	size_t		j;
	char		*expanded_str;
	const char	*value;
	int			start;

	expanded_str = alloc_arena(arena, get_expanded_len(str, exit_status) + 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			expanded_str[j++] = str[i++];
			while (str[i] && str[i] != '\'')
				expanded_str[j++] = str[i++];
			if (str[i] == '\'')
				expanded_str[j++] = str[i++];
		}
		else if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1]) || str[i + 1] == '?'))
		{
			i++;
			if (str[i] == '?')
			{
				value = get_variable_value("?", exit_status, arena);
				if (value)
				{
					ft_memcpy(&expanded_str[j], value, ft_strlen(value));
					j+= ft_strlen(value);
				}
				i++;
			}
			else
			{
				start = i;
				while (str[i] && ft_isalnum(str[i]))
					i++;
				char	var_name[i - start + 1];
				ft_strlcpy(var_name, &str[start], i - start + 1);
				value = get_variable_value(var_name, exit_status, arena);
				if (value)
				{
					ft_memcpy(&expanded_str[j], value, ft_strlen(value));
					j += ft_strlen(value);
				}
			}
		}
		else
			expanded_str[j++] = str[i++];
	}
	expanded_str[j] = '\0';
	return (expanded_str);
}

static char		*get_variable_value(const char *var_name, int exit_status, t_arena *arena)
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
