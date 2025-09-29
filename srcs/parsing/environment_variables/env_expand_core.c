#include "../../../incls/prototypes.h"

static void	expand_args(t_command *cmd, t_arena *arena, int exit_status, t_env *env_list);
static char	*copy_expanded_str(const char *str, int exit_status, t_arena *arena, t_env *env_list);
static int	process_char(const char **str, char **expand_str, int exit_status, t_env *env_list);

void	expand_commands(t_command *cmd_list, t_arena *arena, int exit_status, t_env *env_list)
{
	t_command	*current_cmd;
	t_redir		*current_redir;

	current_cmd = cmd_list;
	current_redir = NULL;
	while (current_cmd)
	{
		expand_args(current_cmd, arena, exit_status, env_list);
		current_redir = current_cmd->redirs;
		while (current_redir)
		{
			if (current_redir->type != HEREDOC_TOKEN)
			{
				current_redir->filename = copy_expanded_str(current_redir->filename,
										exit_status, arena, env_list);
			}
			current_redir = current_redir->next;
		}
		current_cmd = current_cmd->next;
	}
}

static void	expand_args(t_command *cmd, t_arena *arena, int exit_status, t_env *env_list)
{
	char	**tmp_args;

	tmp_args = cmd->args;
	while (tmp_args && *tmp_args)
	{
		*tmp_args = copy_expanded_str(*tmp_args, exit_status, arena, env_list);
		tmp_args++;
	}
}

static char	*copy_expanded_str(const char *str, int exit_status, t_arena *arena, t_env *env_list)
{
	char	*expand_str;
	char	*current_expand_pos;
	size_t	pre_calc_len;

	pre_calc_len = get_expand_len(str, exit_status, env_list);
	expand_str = alloc_arena(arena, pre_calc_len + 1);
	if (!expand_str)
		return (NULL);
	ft_memset(expand_str, 0, pre_calc_len +1);
	current_expand_pos = expand_str;
	while (*str)
	{
		if (process_char(&str, &current_expand_pos, exit_status, env_list) != 0)
			break ;
	}
	*current_expand_pos = '\0';
	if (current_expand_pos == expand_str)
		return (NULL);
	return (expand_str);
}

static int	process_char(const char **str, char **expand_str, int exit_status, t_env *env_list)
{
	if (**str == '\'')
		handle_single_quote(str, expand_str);
	else if (**str == '"')
		handle_double_quote(str, expand_str, exit_status, env_list);
	else if (**str == '$' && is_expand_char(*(*str + 1)))
		handle_var_expand(str, expand_str, exit_status, env_list);
	else
		copy_char(str, expand_str);
	return (0);
}

void	copy_char(const char **str, char **expand_str)
{
	*(*expand_str)++ = *(*str)++;
}
