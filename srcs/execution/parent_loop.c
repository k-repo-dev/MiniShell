#include "../../incls/prototypes.h"

static int	execute_pipeline(t_command *md_list, t_env **env_list);
static void	handle_redirs(t_redir *redirs);
static int	execute_builtins(t_command *cmd_list, t_env **env_list,
				int last_status);
static int	is_builtin(const char *cmd);
static int	count_cmds(t_command *cmd_list);

int	parent_loop(t_command *cmd_list, t_env **env_list, int last_status)
{
	int	exit_status;
	printf("Entered parent_loop\n");
	if (is_builtin(cmd_list->args[0]))
	{
		printf("parent_loop: Going to execute built-in\n");
		exit_status = execute_builtins(cmd_list, env_list, last_status);
		return (exit_status);
	}
	else
	{
		printf("parent_loop: Going to executut pipeine\n");
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
		printf("Parent: Processing ccommand '%s' with in_fd %d\n", cmd_list->args[0], in_fd);
		pid = fork();
				if (pid == -1)
		{
			perror("fork");
			free(pids);
			return (-1);
		}
		if (pid == 0)
		{
			printf("Child %d: in_fd is %d\n", getpid(), in_fd);
			if (in_fd != 0)
			{
				printf("Child %d: Redirecting STDIN (0) to in_fd %d\n", getpid(), in_fd);
				dup2(in_fd, STDIN_FILENO);
				close(in_fd);
			}
			if (cmd_list->next)
			{
				printf("Child %d: Redirecting STDOUT (1) to pipe write end %d\n", getpid(), pipe_fds[1]);
				dup2(pipe_fds[1], STDOUT_FILENO);
				printf("Child %d: Closing unused pipe ends %d and %d\n", getpid(), pipe_fds[0], pipe_fds[1]);
				close(pipe_fds[0]);
				close(pipe_fds[1]);
			}
			handle_redirs(cmd_list->redirs);
			// execve(cmd_list->args[0], cmd_list->args, envp);
			execve_wrapper(cmd_list, env_list);
			perror("minishell");
			exit(127);
		}
		else
		{
			printf("Parent: Forked child with PID %d\n", pid);
			pids[i++] = pid;
			if (in_fd != 0)
			{
				printf("Parent: Closing old in_fd %d\n", in_fd);
				close(in_fd);
			}
			if (cmd_list->next)
			{
				printf("Parent: Creating pipe [%d, %d] and closing write end %d\n", pipe_fds[0], pipe_fds[1], pipe_fds[1]);
				close(pipe_fds[1]);
				in_fd = pipe_fds[0];
			}
		}
		cmd_list = cmd_list->next;
	}
	if (in_fd != 0)
		close(in_fd);
	printf("Parent: All children forked. Waiting for them to finish...\n");
	int j = 0;
	while (j < num_cmds)
	{
			waitpid(pids[j], &exit_status, 0);
		j++;
	}
	printf("Parent: All children finished. Exiting pipeline.\n");
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
