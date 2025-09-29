#include "../../../incls/prototypes.h"

static int	setup_new_redir(t_redir *new_redir, t_token **token, t_arena *arena);
static void	link_new_redir(t_command *cmd, t_redir *new_redir);

void	add_arg_to_cmd(t_command *cmd, t_token *token, t_arena *arena)
{
	char	**new_args;
	int		i;
	int		count;

	count = 0;
	i = 0;
	if (cmd->args)
		while (cmd->args[count])
			count++;
	new_args = alloc_arena(arena, sizeof(char *) * (count + 2));
	while (i < count)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = arena_strdup(arena, token->value);
	new_args[i + 1] = NULL;
	cmd->args = new_args;
}

int add_redir_to_cmd(t_command *cmd, t_token **token, t_arena *arena)
{
	t_redir	*new_redir;
	int		error_flag;

	error_flag = 0;
	new_redir = alloc_arena(arena, sizeof(t_redir));
	if (!new_redir)
		return (1);
	ft_memset(new_redir, 0, sizeof(t_redir));
	error_flag = setup_new_redir(new_redir, token, arena);
	if (error_flag)
		return (1);
	link_new_redir(cmd, new_redir);
	*token = (*token)->next;

	return (0);
}

static int	setup_new_redir(t_redir *new_redir, t_token **token, t_arena *arena)
{
	new_redir->type = (*token)->type;
	*token = (*token)->next;
	if (*token)
	{
		ft_putstr_fd("syntax error: redirection requires argument\n", 2);
		return (1);
	}
	if (new_redir->type == HEREDOC_TOKEN)
		new_redir->filename = handle_heredoc((*token)->value);
	else
		new_redir->filename = arena_strdup(arena, (*token)->value);
	if (!new_redir->filename)
		return (1);
	return (0);
}

static void	link_new_redir(t_command *cmd, t_redir *new_redir)
{
	t_redir	*current_redir;

	current_redir = NULL;
	if (!cmd->redirs)
		cmd->redirs = new_redir;
	else
	{
		current_redir = cmd->redirs;
		while (current_redir->next)
			current_redir = current_redir->next;
	}
}
