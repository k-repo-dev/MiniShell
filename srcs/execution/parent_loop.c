#include "../../incls/prototypes.h"

static int	execute_pipeline(t_command *md_list, t_env **env_list);
static void	handle_redirs(t_redir *redirs);
static int	execute_builtins(t_command *cmd_list, t_env **env_list,
				int last_status);
static int	is_builtin(const char *cmd);
static int	count_cmds(t_command *cmd_list);
static int	is_parent_builtin(const char *cmd);

int	parent_loop(t_command *cmd_list, t_env **env_list, int last_status)
{
	int	exit_status;
	if (is_parent_builtin(cmd_list->args[0]) && cmd_list->next == NULL)
	{
		exit_status = execute_builtins(cmd_list, env_list, last_status);
		return (exit_status);
	}
	else
	{
		exit_status = execute_pipeline(cmd_list, env_list);
		return (exit_status);
	}
	return (0);
}

static int	execute_pipeline(t_command *cmd_list, t_env **env_list)
{
	pid_t	*pids;
	int		pid;
	int		pipe_fds[2];
	int		in_fd;
	int		exit_status;
	int		num_cmds;
	int		i;

	i = 0;
	num_cmds = count_cmds(cmd_list);
	in_fd = 0;
	pids = malloc(sizeof(pid_t) * num_cmds);
	if (!pids)
	{
		perror("malloc");
		return (-1);
	}
	while (cmd_list)
	{
		if (cmd_list->next)
		{
			if (pipe(pipe_fds) == -1)
			{
				perror("pipe");
				free(pids);
				return (-1);
			}
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			free(pids);
			return (-1);
		}
		if (pid == 0)
		{
			if (in_fd != 0)
			{
				dup2(in_fd, STDIN_FILENO);
				close(in_fd);
			}
			if (cmd_list->next)
			{
				dup2(pipe_fds[1], STDOUT_FILENO);
				close(pipe_fds[0]);
				close(pipe_fds[1]);
			}
			handle_redirs(cmd_list->redirs);
			if (is_builtin(cmd_list->args[0]))
			{
				exit_status = handle_builtins(cmd_list, env_list, 0);
				exit(exit_status);
			}
			execve_wrapper(cmd_list, env_list);
			if (errno == ENOENT)
				exit(handle_error(E_CMD_NOT_FOUND, cmd_list->args[0]));
			else if (errno == EACCES)
				exit(handle_error(E_PERMISSION_DENIED, cmd_list->args[0]));
			else
				exit(handle_error(E_CMD_NOT_FOUND, cmd_list->args[0]));
		}
		else
		{

			pids[i++] = pid;
			if (in_fd != 0)
				close(in_fd);
			if (cmd_list->next)
			{
				close(pipe_fds[1]);
				in_fd = pipe_fds[0];
			}
		}
		cmd_list = cmd_list->next;
	}
	if (in_fd != 0)
		close(in_fd);
	int j = 0;
	while (j < num_cmds)
	{
			waitpid(pids[j], &exit_status, 0);
		j++;
	}
	return (WEXITSTATUS(exit_status));
}

static int	count_cmds(t_command *cmd_list)
{
	int	count;

	count = 0;
	while (cmd_list)
	{
		count++;
		cmd_list = cmd_list->next;
	}
	return (count);
}

static void	handle_redirs(t_redir *redirs)
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
				exit_code = handle_file_error(redirs->filename, "Permission denied");
			else
				exit_code = handle_file_error(redirs->filename, "No such file or dirextory");
			exit(exit_code);
		}
		if (redirs->type == GREAT_TOKEN || redirs->type == APPEND_TOKEN)
		{

			if (dup2(fd, STDOUT_FILENO) == -1)
				exit(1);
		}
		else
		{
			if (dup2(fd, STDIN_FILENO) == -1)
				exit(1);
		}
		close(fd);
		redirs = redirs->next;
	}
}

static int	execute_builtins(t_command *cmd, t_env **env_list, int last_status)
{
	return (handle_builtins(cmd, env_list, last_status));
}

static int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

static int	is_parent_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}
