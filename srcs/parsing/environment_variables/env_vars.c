#include "../../../incls/prototypes.h"

static char	*copy_expanded_str(const char *str, int exit_status,
					t_arena *arena, t_env *env_list);
static void	handle_single_quote(const char **str, char **expand_str);
static void	handle_var_expand(const char **str, char **expand_str, int exit_status, t_arena *arena, t_env *env_list);
static void	expand_normal_var(const char **str, char **expand_str, t_arena *arena, t_env *env_list);

void	expand_commands(t_command *cmd_list, t_arena *arena, int exit_status, t_env *env_list)
{
	t_command	*current_cmd;
	t_redir		*current_redir;
	char		**tmp_args;

	current_cmd = cmd_list;
	while (current_cmd)
	{
		tmp_args = current_cmd->args;
		while (tmp_args && *tmp_args)
		{
			*tmp_args = copy_expanded_str(*tmp_args, exit_status, arena, env_list);
			tmp_args++;
		}
		current_redir = current_cmd->redirs;
		while (current_redir)
		{
			current_redir->filename = copy_expanded_str(current_redir->filename, exit_status, arena, env_list);
			current_redir = current_redir->next;
		}
		current_cmd = current_cmd->next;
	}
}

static char	*copy_expanded_str(const char *str, int exit_status, t_arena *arena, t_env *env_list)
{
	char		*expand_str;
	char		*current_expand_pos;
	const char	*current_str_pos;
	size_t		len;

	len = ft_strlen(str + 1);
	expand_str = alloc_arena(arena, len * 2);
	if (!expand_str)
		return (NULL);
	current_expand_pos = expand_str;
	current_str_pos = str;
	while (*current_str_pos)
	{
		if (*current_str_pos == '\'')
			handle_single_quote(&current_str_pos, &current_expand_pos);
		else if (*current_str_pos == '$' && *(current_str_pos + 1)
				&& (ft_isalnum(*(current_str_pos + 1)) || *(current_str_pos + 1) == '?'))
			handle_var_expand(&current_str_pos, &current_expand_pos, exit_status, arena, env_list);
		else
			*current_expand_pos++ = *current_str_pos++;
	}
	*current_expand_pos = '\0';
	return (expand_str);
}

static void	handle_single_quote(const char **str, char **expand_str)
{
	*(*expand_str)++ = *(*str)++;
	while (**str && **str != '\'')
		*(*expand_str)++ = *(*str)++;
	if (**str == '\'')
		*(*expand_str)++ = *(*str)++;
}

static void handle_var_expand(const char **str, char **expand_str, int exit_status, t_arena *arena, t_env *env_list)
{
	const char	*value;
	char		*tmp_value;

	(*str)++;
	if (**str == '?')
	{
		tmp_value = ft_itoa(exit_status);
		value = tmp_value;
		while (*value)
			*(*expand_str)++ = *value++;
		free(tmp_value);
		(*str)++;
	}
	else
		expand_normal_var(str, expand_str, arena, env_list);
}

static void	expand_normal_var(const char **str, char **expand_str, t_arena *arena, t_env *env_list)
{
	const char	*value;
	const char	*start;
	char		*var_name;
	size_t		len;

	start = *str;
	while (**str && (ft_isalnum(**str) || **str == '_'))
		(*str)++;
	len = *str - start;
	var_name = alloc_arena(arena, len + 1);
	ft_strlcpy(var_name, start, len + 1);
	value = get_env_value(env_list, var_name);
	if (value)
	{
		while (*value)
			*(*expand_str)++ = *value++;
	}
}
/*static char	*copy_expanded_str(const char *str, int exit_status, t_arena *arena)
{
	size_t		i;
	size_t		j;
	char		*expanded_str;
	const char	*value;
	int			start;
	char		var_name;

	expanded_str = alloc_arena(arena, get_expanded_len(str, exit_status) + 1);
	i = 0;
	j = 0;
	start = 0;
	var_name = i - start + 1;
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
		else if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1]) || str[i
				+ 1] == '?'))
		{
			i++;
			if (str[i] == '?')
			{
				value = get_variable_value("?", exit_status, arena);
				if (value)
				{
					ft_memcpy(&expanded_str[j], value, ft_strlen(value));
					j += ft_strlen(value);
				}
				i++;
			}
			else
			{
				start = i;
				while (str[i] && ft_isalnum(str[i]))
					i++;
				ft_strlcpy(&var_name, &str[start], i - start + 1);
				value = get_variable_value(&var_name, exit_status, arena);
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
}*/
