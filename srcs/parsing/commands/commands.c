#include "../../../incls/prototypes.h"

static int			process_token(t_command **current_cmd,
						t_token **current_token, t_command **cmd_head,
						t_arena *arena);
static int			redir_handler(t_command *cmd, t_token **token,
						t_arena *arena);
static t_command	*create_and_link_cmd(t_command **cmd_head, t_arena *arena);
static t_command	*get_last_cmd(t_command *cmd_head);

t_command	*parse_commands(t_token *token_head, t_arena *arena)
{
	t_command	*cmd_head;
	t_command	*current_cmd;
	t_token		*current_token;
	int			error_flag;

	cmd_head = NULL;
	current_cmd = NULL;
	current_token = token_head;
	error_flag = 0;
	while (current_token && !error_flag)
	{
		error_flag = process_token(&current_cmd, &current_token, &cmd_head,
				arena);
		if (error_flag == 0 && current_token)
			current_token = current_token->next;
	}
	if (error_flag)
		return (NULL);
	return (cmd_head);
}

static int	process_token(t_command **current_cmd, t_token **current_token,
		t_command **cmd_head, t_arena *arena)
{
	t_token	*token;

	token = *current_token;
	if (!(*current_cmd))
	{
		*current_cmd = create_and_link_cmd(cmd_head, arena);
		if (!(*current_cmd))
			return (1);
	}
	if (token->type == PIPE_TOKEN)
		*current_cmd = NULL;
	else if (token->type == LESS_TOKEN || token->type == GREAT_TOKEN
		|| token->type == HEREDOC_TOKEN || token->type == APPEND_TOKEN)
	{
		if (redir_handler(*current_cmd, current_token, arena) != 0)
			return (1);
	}
	else
		add_arg_to_cmd(*current_cmd, token, arena);
	return (0);
}

static int	redir_handler(t_command *cmd, t_token **token, t_arena *arena)
{
	if (!(*token)->next)
		return (handle_error(E_SYNTAX_ERROR, "missing filename"));
	*token = (*token)->next;
	if (add_redir_to_cmd(cmd, token, arena) != 0)
		return (1);
	return (0);
}

static t_command	*create_and_link_cmd(t_command **cmd_head, t_arena *arena)
{
	t_command	*new_cmd;
	t_command	*last_cmd;

	new_cmd = alloc_arena(arena, sizeof(t_command));
	if (!new_cmd)
		return (NULL);
	ft_memset(new_cmd, 0, sizeof(t_command));
	if (!*cmd_head)
		*cmd_head = new_cmd;
	else
	{
		last_cmd = get_last_cmd(*cmd_head);
		last_cmd->next = new_cmd;
	}
	return (new_cmd);
}

static t_command	*get_last_cmd(t_command *cmd_head)
{
	t_command	*last_cmd;

	last_cmd = cmd_head;
	while (last_cmd->next)
		last_cmd = last_cmd->next;
	return (last_cmd);
}
