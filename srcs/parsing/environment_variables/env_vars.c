#include "../../../incls/prototypes.h"

static char	*copy_expanded_str(const char *str, int exit_status, t_arena *arena,
				t_env *env_list);
static void	handle_single_quote(const char **str, char **expand_str);
static void	handle_var_expand(const char **str, char **expand_str,
				int exit_status, t_env *env_list);
static void	expand_normal_var(const char **str, char **expand_str, t_env *env_list);
static void	handle_double_quote(const char **str, char **expanded_str, int exit_status, t_env *env_list);

void	expand_commands(t_command *cmd_list, t_arena *arena, int exit_status,
		t_env *env_list)
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
			*tmp_args = copy_expanded_str(*tmp_args, exit_status, arena,
					env_list);
			tmp_args++;
		}
		current_redir = current_cmd->redirs;
		while (current_redir)
		{
			if (current_redir->type != HEREDOC_TOKEN)
				current_redir->filename = copy_expanded_str(current_redir->filename,
						exit_status, arena, env_list);
			current_redir = current_redir->next;
		}
		current_cmd = current_cmd->next;
	}
}

static char	*copy_expanded_str(const char *str, int exit_status, t_arena *arena,
		t_env *env_list)
{
	char		*expand_str;
	char		*current_expand_pos;
	const char	*current_str_pos;
	size_t		pre_calc_len;

	pre_calc_len = get_expanded_len(str, exit_status, env_list);
	expand_str = alloc_arena(arena, pre_calc_len + 1);
	if (!expand_str)
		return (NULL);
	ft_memset(expand_str, 0, pre_calc_len + 1);
	current_expand_pos = expand_str;
	current_str_pos = str;
	while (*current_str_pos)
	{
		if (*current_str_pos == '\'')
			handle_single_quote(&current_str_pos, &current_expand_pos);
		else if (*current_str_pos == '"')
			handle_double_quote(&current_str_pos, &current_expand_pos, exit_status, env_list);
		else if (*current_str_pos == '$' && *(current_str_pos + 1)
			&& (ft_isalnum(*(current_str_pos + 1)) || *(current_str_pos
					+ 1) == '?'))
			handle_var_expand(&current_str_pos, &current_expand_pos,
				exit_status, env_list);
		else
			*current_expand_pos++ = *current_str_pos++;
	}
	*current_expand_pos = '\0';
	if (current_expand_pos == expand_str)
		return (NULL);
	return (expand_str);
}

static void	handle_single_quote(const char **str, char **expand_str)
{
	(*str)++;
	while (**str && **str != '\'')
		*(*expand_str)++ = *(*str)++;
	if (**str == '\'')
		(*str)++;
}

static void	handle_var_expand(const char **str, char **expand_str,
		int exit_status, t_env *env_list)
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
		expand_normal_var(str, expand_str,  env_list);
}

static void	expand_normal_var(const char **str, char **expand_str, t_env *env_list)
{
	const char	*value;
	const char	*start;
	char		var_name[256];
	size_t		len;

	start = *str;
	while (**str && (ft_isalnum(**str) || **str == '_'))
		(*str)++;
	len = *str - start;
	if (len >= 256)
		return ;
	ft_strlcpy(var_name, start, len + 1);
	value = get_env_value(env_list, var_name);
	if (value)
	{
		while (*value)
			*(*expand_str)++ = *value++;
	}
}

static void	handle_double_quote(const char **str, char **expand_str, int exit_status, t_env *env_list)
{
	(*str)++;
	while (**str && **str != '"')
	{
		if (**str == '$' && *(*str + 1) && (ft_isalnum(*(*str + 1)) || *(*str + 1) == '?'))
		{
			handle_var_expand(str, expand_str, exit_status, env_list);
		}
		else
			*(*expand_str)++ = *(*str)++;
	}
	if (**str == '"')
		(*str)++;
}
