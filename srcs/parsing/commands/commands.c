#include "../../../incls/prototypes.h"

static void	add_arg_to_cmd(t_command *cmd, t_token *token, t_arena *arena);
static void add_redir_to_cmd(t_command *cmd, t_token **token, t_arena *arena);

t_command	*parse_command(t_token *token_head, t_arena *arena)
{
	t_command	*cmd_head;
	t_command	*current_cmd;
	t_token		*current_token;

	cmd_head = NULL;
	current_cmd = NULL;
	current_token = token_head;
	while (current_token)
	{
		if (!current_cmd)
		{
			current_cmd = alloc_arena(arena, sizeof(t_command));
			current_cmd->next = NULL;
			current_cmd->args = NULL;
			current_cmd->redirects = NULL;
			if (!cmd_head)
				cmd_head = current_cmd;
		}
		if (current_token->type == PIPE_TOKEN)
			current_cmd = current_cmd->next;
		else if (current_token->type == LESS_TOKEN || current_token->type == GREAT_TOKEN)
			add_redir_to_cmd(current_cmd, &current_token, arena);
		else
			add_arg_to_cmd(current_cmd, current_token, arena);
		current_token = current_token->next;
	}
	return (cmd_head);
}

static void	add_arg_to_cmd(t_command *cmd, t_token *token, t_arena *arena)
{

}

static void add_redir_to_cmd(t_command *cmd, t_token **token, t_arena *arena)
{

}
