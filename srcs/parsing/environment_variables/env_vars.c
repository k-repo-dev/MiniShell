#include "../../../incls/prototypes.h"

static char		*expand_str(const char *str, int exit_status, t_arena *arena);
static size_t	get_expanded_len(const char *str, int exit_status, t_arena *arena);
static void		copy_expanded_str(char *dest, const char *src, int exit_status, t_arena *arena);
static char		*get_variable_value(const char *var_name, int exit_status, t_arena *arena);

void	expand_command(t_command *cmd_list, t_arena *arena, int exit_status)
{
	t_command	*current_cmd;
	char		**args;
	char		**tmp_args;

	current_cmd = cmd_list;
	while (current_cmd)
	{
		args = current_cmd->args;
		tmp_args = args;
		while (*tmp_args)
		{
			*tmp_args = expand_str(*tmp_args, exit_status, arena);
			tmp_args++;
		}
		current_cmd = current_cmd->next;
	}
}

static char	*expand_str(const char *str, int exit_status, t_arena *arena)
{
	char	*expanded_str;
	size_t	len;

	len = get_expanded_len(str, exit_status, arena);
	expanded_str = alloc_arena(arena, len + 1);
	copy_expanded_str(expanded_str, str, exit_status, arena);
	return (expanded_str);
}

static size_t	get_expanded_len(const char *str, int exit_status, t_arena *arena)
{
	size_t	len;
	size_t	i;
	char	*var_value;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			len++;
			while (str[++i] && str[i] != '\'')
				len++;
			if (str[i])
				len++;
		}
		else if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1]) && str[i + 1]) == '?')
		{
			i++;
			if (str[i] == '?')
				var_value = get_variable_value("?", exit_status, arena);
			else
				var_value = getenv(&str[i]);
			if (var_value)
				len += ft_strlen(var_value);
			while (ft_isalnum(str[i]))
				i++;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

static void	copy_expanded_str(char *dest, const char *src, int exit_status, t_arena *arena)
{
	size_t	i;
	size_t	j;
	char	*var_value;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] == '\'')
		{
			dest[j++] = src[i++];
			while (src[i] && src[i] != '\'')
				dest[j++] = src[i++];
			if (src[i])
				dest[j++] = src[i++];
		}
		else if (src[i] == '$' && src[i + 1] && (ft_isalnum(src[i + 1]) || src[i + 1] == '?'))
		{
			i++;
			if (src[i] == '?')
				var_value = get_variable_value("?", exit_status, arena);
			else
				var_value = getenv(&src[i]);
			if (var_value)
				while (*var_value)
					dest[j++] = *var_value++;
			while (ft_isalnum(src[i]))
				i++;
		}
		else
			dest[j++] = src[i++];
	}
	dest[j] = '\0';
}

static char		*get_variable_value(const char *var_name, int exit_status, t_arena *arena)
{
	if (!ft_strcmp(var_name, "?"))
		return (arena_itoa(exit_status, arena));
	return (getenv(var_name));
}
