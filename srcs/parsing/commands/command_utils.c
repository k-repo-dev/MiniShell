#include "../../../incls/prototypes.h"

static char	*handle_heredoc(const char *delimiter);
static void	heredoc_warning(const char *delimiter);
static int	get_heredoc_id(void);

void	add_arg_to_cmd(t_command *cmd, t_token *token, t_arena *arena)
{
	char	**new_args;
	int		i;
	int		count;

	if (!cmd || !token || !arena)
	{
		ft_putstr_fd("add_arg_to_cmd: NULL pointer received\n", 2);
		return ;
	}
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

int	add_redir_to_cmd(t_command *cmd, t_token **token, t_arena *arena)
{
	t_redir	*new_redir;
	t_redir	*current_redir;

	new_redir = alloc_arena(arena, sizeof(t_redir));
	if (!new_redir)
		return (1);
	ft_memset(new_redir, 0, sizeof(t_redir));
	new_redir->type = (*token)->type;
	if (!*token)
	{
		ft_putstr_fd("syntax error: redirection requires argument\n", 2);
		return (1);
	}
	if (new_redir->type == HEREDOC_TOKEN)
		new_redir->filename = handle_heredoc((*token)->next->value);
	else
		new_redir->filename = arena_strdup(arena, (*token)->next->value);
	if (!new_redir->filename)
		return (1);
	if (!cmd->redirs)
		cmd->redirs = new_redir;
	else
	{
		current_redir = cmd->redirs;
		while (current_redir->next)
			current_redir = current_redir->next;
		current_redir->next = new_redir;
	}
	*token = (*token)->next;
	return (0);
}

static char	*handle_heredoc(const char *delimiter)
{
	char	*line;
	char	*id_str;
	char	*tmp_filename;
	int		fd;
	int		id;
	size_t	len;

	id = get_heredoc_id();
	id_str = ft_itoa(id);
	if (!id_str)
		return (NULL);
	len = 11 + ft_strlen(id_str) + 1;
	tmp_filename = (char *)malloc(len);
	if (!tmp_filename)
	{
		free(id_str);
		return (NULL);
	}
	ft_strlcpy(tmp_filename, "/tmp/ms_hd_", len);
	ft_strlcat(tmp_filename, id_str, len);
	free(id_str);
	fd = open(tmp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open heredoc file");
		free(tmp_filename);
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
	return (tmp_filename);
}

static int	get_heredoc_id(void)
{
	static int	id;

	// id = 0;
	return (++id);
}

static void	heredoc_warning(const char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document at line 1 delimited by end-of0-file (wanted '",
		2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}
