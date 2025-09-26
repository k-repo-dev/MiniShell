#include "../../../incls/prototypes.h"

static char	*handle_heredoc(const char *delimiter, t_arena *arena);
static void	heredoc_warning(const char *delimiter);

void	add_arg_to_cmd(t_command *cmd, t_token *token, t_arena *arena)
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

int add_redir_to_cmd(t_command *cmd, t_token **token, t_arena *arena)
{
	t_redir	*new_redir;
	t_redir	*current_redir;

	new_redir = alloc_arena(arena, sizeof(t_redir));
	if (!new_redir)
		return (1);
	ft_memset(new_redir, 0, sizeof(t_redir));
	new_redir->type = (*token)->type;
	*token = (*token)->next;
	if (!*token)
	{
		ft_putstr_fd("syntax error\n", 2);
		return (1);
	}
	if (new_redir->type == HEREDOC_TOKEN)
		new_redir->filename = handle_heredoc((*token)->value, arena);
	else
		new_redir->filename = arena_strdup(arena, (*token)->value);
	if (!cmd->redirs)
		cmd->redirs = new_redir;
	else
	{
		current_redir = cmd->redirs;
		while (current_redir->next)
			current_redir = current_redir->next;
		current_redir->next = new_redir;
	}
	return (0);
}

static char	*handle_heredoc(const char *delimiter, t_arena *arena)
{
	char	*line;
	int		fd;
	char	*tmp_filename;

	if (!(tmp_filename = arena_strdup(arena, "/tmp/heredoc_XXXXXX"))
			|| (fd = mkstemp(tmp_filename)) == -1)
	{
		perror("Error: mkstmp");
		return (NULL);
	}
	while ((line = readline("> ")))
	{
		if (!ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	if (!line)
		heredoc_warning(delimiter);
	close(fd);
	return(tmp_filename);
}

static void	heredoc_warning(const char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document at line 1 delimited by end-of0-file (wanted '", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}
