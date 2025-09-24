#include "prototypes.h"

static int	execute_pipeline(t_command *md_list, t_env **env_list);
static void	handle_redirs(t_redir *redirs);
static int	execute_builtins(t_command *cmd_list, t_env **env_list,
				int last_status);
static int	is_builtin(const char *cmd);

int	parent_loop(t_command *cmd_list, t_env **env_list, int last_status)
{
	int	exit_status;

	if (is_builtin(cmd_list->args[0]))
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
	pid_t	pid;
	int		pipe_fds[2];
	int		in_fd;
	int		exit_status;
	t_arena	arena;

	in_fd = 0;
	while (cmd_list)
	{
		init_arena(&arena, 1024);
		if (cmd_list->next)
			pipe(pipe_fds);
		pid = fork();
		if (pid == -1)
			return (-1);
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
			// execve(cmd_list->args[0], cmd_list->args, envp);
			execve_wrapper(cmd_list, env_list);
			perror("minishell");
			exit(127);
		}
		waitpid(pid, &exit_status, 0);
		if (in_fd != 0)
			close(in_fd);
		if (cmd_list->next)
		{
			close(pipe_fds[1]);
			in_fd = pipe_fds[0];
		}
		free_arena(&arena);
		cmd_list = cmd_list->next;
	}
	return (exit_status);
}

static void	handle_redirs(t_redir *redirs)
{
	int	fd;

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
			perror("minishell");
			exit(1);
		}
		if (redirs->type == GREAT_TOKEN || redirs->type == APPEND_TOKEN)
			dup2(fd, STDOUT_FILENO);
		else
			dup2(fd, STDIN_FILENO);
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
