#include "execution.h"
#include "minishell.h"

static void	child(int prev_fd, int pipe_fd[2], t_command *cmd, char **envp);

void	parent_loop(t_command **command_list, char **envp)
{
	t_command	*cmd;
	pid_t		pid;
	int			status;
	int			pipe_fd[2];
	int			prev_fd;

	prev_fd = -1;
	cmd = *command_list;
	test_print(command_list);
	while (cmd)
	{
		if (!cmd->next && is_builtin(cmd->args[0]))
			parent_builtin(&cmd, envp);
		if (cmd->next)
			pipe(pipe_fd);
		if ((pid = fork()) == 0) // Child process
			child(prev_fd, pipe_fd, cmd, envp);
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		cmd = cmd->next;
	}
	while (wait(&status) > 0)
		;
}

static void	child(int prev_fd, int pipe_fd[2], t_command *cmd, char **envp)
{
	if (prev_fd != -1)
		dup2(prev_fd, STDIN_FILENO);
	if (cmd->next)
		dup2(pipe_fd[1], STDOUT_FILENO);
	if (prev_fd != -1)
		close(prev_fd);
	if (cmd->next)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	execve_wrapper(cmd, envp);
	exit(1);
}
