#include "../../../incls/prototypes.h"

static t_command	*create_and_link_cmd(t_command **cmd_head, t_arena *arena);
/*static void	add_arg_to_cmd(t_command *cmd, t_token *token, t_arena *arena);
static void add_redir_to_cmd(t_command *cmd, t_token **token, t_arena *arena);
static char	*handle_heredoc(const char *delimiter, t_arena *arena);*/

t_command	*parse_commands(t_token *token_head, t_arena *arena)
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
			current_cmd = create_and_link_cmd(&cmd_head, arena);
			if (!current_cmd)
				return (NULL);
		}
		if (current_token->type == PIPE_TOKEN)
			current_cmd = NULL;
		else if (current_token->type == LESS_TOKEN || current_token->type == GREAT_TOKEN
				|| current_token->type == HEREDOC_TOKEN || current_token->type == APPEND_TOKEN)
			add_redir_to_cmd(current_cmd, &current_token, arena);
		else
			add_arg_to_cmd(current_cmd, current_token, arena);
		current_token = current_token->next;
	}
	return (cmd_head);
}

static t_command	*create_and_link_cmd(t_command **cmd_head, t_arena *arena)
{
	t_command	*new_cmd;
	t_command	*last_cmd;

	new_cmd = alloc_arena(arena, sizeof(t_command));
	if (!new_cmd)
		return (NULL);
	new_cmd->next = NULL;
	new_cmd->args = NULL;
	new_cmd->redirects = NULL;
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
/*t_command	*parse_commands(t_token *token_head, t_arena *arena)
{
	t_command	*cmd_head;
	t_command	*current_cmd;
	t_token		*current_token;
	t_command	*tmp;

	cmd_head = NULL;
	current_cmd = NULL;
	current_token = token_head;
	while (current_token)
	{
		if (!current_cmd)
		{
			current_cmd = alloc_arena(arena, sizeof(t_command));
			if (!current_cmd)
				return (NULL);
			current_cmd->next = NULL;
			current_cmd->args = NULL;
			current_cmd->redirects = NULL;
			if (!cmd_head)
				cmd_head = current_cmd;
			else
			{
				tmp = cmd_head;
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = current_cmd;
			}
		}
		if (current_token->type == PIPE_TOKEN)
			current_cmd = current_cmd->next;
		else if (current_token->type == LESS_TOKEN || current_token->type == GREAT_TOKEN
					|| current_token->type == HEREDOC_TOKEN || current_token->type == APPEND_TOKEN)
			add_redir_to_cmd(current_cmd, &current_token, arena);
		else
			add_arg_to_cmd(current_cmd, current_token, arena);
		current_token = current_token->next;
	}
	return (cmd_head);
}*/


/*static void	add_arg_to_cmd(t_command *cmd, t_token *token, t_arena *arena)
{
	char	**new_args;
	int		i;
	int		count;

	count = 0;
	if (cmd->args)
		while (cmd->args[count])
			count++;
	new_args = alloc_arena(arena, sizeof(char *) * (count + 2));
	i = 0;
	while (i < count)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = arena_strdup(arena, token->value);
	new_args[i + 1] = NULL;
	cmd->args = new_args;
}

static void add_redir_to_cmd(t_command *cmd, t_token **token, t_arena *arena)
{
	t_redir	*new_redir;
	t_redir	*current_redir;

	new_redir = alloc_arena(arena, sizeof(t_redir));
	new_redir->type = (*token)->type;
	*token = (*token)->next;
	if (!*token)
	{
		ft_putstr_fd("syntax error near unexpected token 'newine'\n", 2);
		return ;
	}
	if (new_redir->type == HEREDOC_TOKEN)
		new_redir->filename = handle_heredoc((*token)->value, arena);
	else
		new_redir->filename = arena_strdup(arena, (*token)->value);
	if (!cmd->redirects)
		cmd->redirects = new_redir;
	else
	{
		current_redir = cmd->redirects;
		while (current_redir->next)
			current_redir = current_redir->next;
		current_redir->next = new_redir;
	}
}

static char	*handle_heredoc(const char *delimiter, t_arena *arena)
{
	char	*line;
	int		fd;
	char	*tmp_filename;

	tmp_filename = arena_strdup(arena, "/tmp/heredoc_XXXXXX");
	fd = mkstemp(tmp_filename);
	if (fd == -1)
	{
		perror("mkstemp");
		return (NULL);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minihell: warning: here-document at line 1 delimited by by end-of0file (wanted '", 2);
			ft_putstr_fd(delimiter, 2);
			ft_putstr_fd("')\n", 2);
			break ;
		}
		if (!ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	close(fd);
	return (tmp_filename);
}*/
