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

static void	child_proc(t_command *cmd, t_env **env, int in_fd, int *pipe_fds)
{
    int	exit_status;

    if (in_fd != 0)
    {
        dup2(in_fd, STDIN_FILENO);
        close(in_fd);
    }
    if (cmd->next)
    {
        dup2(pipe_fds[1], STDOUT_FILENO);
        close(pipe_fds[0]);
        close(pipe_fds[1]);
    }
    handle_redirs(cmd->redirs);
    if (is_builtin(cmd->args[0]))
    {
        exit_status = handle_builtins(cmd, env, 0);
        exit(exit_status);
    }
    execve_wrapper(cmd, env);
    perror("minishell");
    exit(127);
}

static int	wait_all(pid_t *pids, int num)
{
    int	status;
    int	i;

    i = 0;
    while (i < num)
    {
        waitpid(pids[i], &status, 0);
        i++;
    }
    return (WEXITSTATUS(status));
}

static int	pipeline_fork_step(
    t_command *cmd, t_env **env, int *in_fd, int *pipe_fds, pid_t *pid)
{
    if (cmd->next && pipe(pipe_fds) == -1)
        return (perror("pipe"), -1);
    *pid = fork();
    if (*pid == -1)
        return (perror("fork"), -1);
    if (*pid == 0)
        child_proc(cmd, env, *in_fd, pipe_fds);
    if (*in_fd != 0)
        close(*in_fd);
    if (cmd->next)
    {
        close(pipe_fds[1]);
        *in_fd = pipe_fds[0];
    }
    return (0);
}

static int	execute_pipeline(t_command *cmd, t_env **env)
{
    pid_t	*pids;
    int		pipe_fds[2];
    int		in_fd;
    int		num;
    int		i;

    num = count_cmds(cmd);
    pids = malloc(sizeof(pid_t) * num);
    if (!pids)
        return (perror("malloc"), -1);
    in_fd = 0;
    i = 0;
    while (cmd)
    {
        if (pipeline_fork_step(cmd, env, &in_fd, pipe_fds, &pids[i]) == -1)
            return (free(pids), -1);
        cmd = cmd->next;
        i++;
    }
    if (in_fd != 0)
        close(in_fd);
    i = wait_all(pids, num);
    free(pids);
    return (i);
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
