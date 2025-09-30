#include "../../../incls/prototypes.h"

int	handle_redirs(t_redir *redirs)
{
	int	fd;
	int	exit_code;

	exit_code = 0;
	while (redirs)
	{
		if (redirs->type == GREAT_TOKEN)
			fd = open(redirs->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redirs->type == APPEND_TOKEN)
			fd = open(redirs->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redirs->type == LESS_TOKEN)
			fd = open(redirs->filename, O_RDONLY);
		else if (redirs->type == HEREDOC_TOKEN)
			fd = open(redirs->filename, O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit_code = handle_file_error(redirs->filename,
						"Permission denied");
			else
				exit_code = handle_file_error(redirs->filename,
						"No such file or directory");
			return (exit_code);
		}
		if (redirs->type == GREAT_TOKEN || redirs->type == APPEND_TOKEN)
		{
			if (dup2(fd, STDOUT_FILENO) == -1)
				return (1);
		}
		else
		{
			if (dup2(fd, STDIN_FILENO) == -1)
				return (1);
		}
		close(fd);
		redirs = redirs->next;
	}
	return (0);
}

void	cleanup_redirs(t_command *cmd_list)
{
	t_command	*cmd;
	t_redir		*redir;

	cmd = cmd_list;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == HEREDOC_TOKEN)
			{
				if (redir->filename)
					unlink(redir->filename);
				if (redir->filename)
					free(redir->filename);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
