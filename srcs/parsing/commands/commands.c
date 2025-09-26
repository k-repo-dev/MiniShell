#include "../../../incls/prototypes.h"

static t_command	*create_and_link_cmd(t_command **cmd_head, t_arena *arena);

t_command	*parse_commands(t_token *token_head, t_arena *arena)
{
	t_command	*cmd_head;
	t_command	*current_cmd;
	t_token		*current_token;
	int			error_flag;

	error_flag = 0;
	cmd_head = NULL;
	current_cmd = NULL;
	current_token = token_head;
	while (current_token && !error_flag)
	{
		if (!current_cmd)
		{
			current_cmd = create_and_link_cmd(&cmd_head, arena);
			if (!current_cmd)
				return (NULL);
		}
		if (current_token->type == PIPE_TOKEN)
			current_cmd = NULL;
		else if (current_token->type == LESS_TOKEN || current_token->type == GREAT_TOKEN
				|| current_token->type == HEREDOC_TOKEN || current_token->type == APPEND_TOKEN)
		{
			if (add_redir_to_cmd(current_cmd, &current_token, arena) != 0)
			{
				error_flag = 1;
				continue ;
			}
		}
		else
			add_arg_to_cmd(current_cmd, current_token, arena);
		current_token = current_token->next;
	}
	if (error_flag)
		return (NULL);
	return (cmd_head);
}

static t_command	*create_and_link_cmd(t_command **cmd_head, t_arena *arena)
{
	t_command	*new_cmd;
	t_command	*last_cmd;

	new_cmd = alloc_arena(arena, sizeof(t_command));
	if (!new_cmd)
		return (NULL);
	ft_memset(new_cmd, 0, sizeof(t_command));
	new_cmd->next = NULL;
	new_cmd->args = NULL;
	new_cmd->redirs = NULL;
	if (!*cmd_head)
		*cmd_head = new_cmd;
	else
	{
		last_cmd = *cmd_head;
		while (last_cmd->next)
			last_cmd = last_cmd->next;
		last_cmd->next = new_cmd;
	}
	return (new_cmd);
}
