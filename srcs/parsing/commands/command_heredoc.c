#include "../../../incls/prototypes.h"

static int	get_heredoc_id(void);
static char	*create_heredoc_filename(int id);
static int	write_heredoc_to_file(int fd, const char *delimiter);
static void	heredoc_warning(const char *delimiter);

char	*handle_heredoc(const char *delimiter)
{
	char	*tmp_filename;
	int		fd;
	int		id;

	id = get_heredoc_id();
	tmp_filename = create_heredoc_filename(id);
	if (!tmp_filename)
		return (NULL);
	fd = open(tmp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open heredoc file");
		free(tmp_filename);
		return (NULL);
	}
	if (write_heredoc_to_file(fd, delimiter) != 0)
	{
		free(tmp_filename);
		return (NULL);
	}
	close(fd);
	return (tmp_filename);
}

static int	get_heredoc_id(void)
{
	static int	id;

	return (++id);
}

static char	*create_heredoc_filename(int id)
{
	char	*id_str;
	char	*tmp_filename;
	size_t	len;

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
	return (tmp_filename);
}

static int	write_heredoc_to_file(int fd, const char *delimiter)
{
	char	*line;

	line = NULL;
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
	return (0);
}

static void	heredoc_warning(const char *delimiter)
{
	ft_putstr_fd("miishell: warning: here-document at line 1 delimited by ", 2);
	ft_putstr_fd("end-of-file (wanted '", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}
