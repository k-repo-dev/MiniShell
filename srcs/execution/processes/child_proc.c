#include "../../../incls/prototypes.h"

void	child_proc(t_command *cmd, t_env **env, int in_fd, int *pipe_fds)
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
	if (cmd->args && cmd->args[0] && is_builtin(cmd->args[0]))
	{
		exit_status = handle_builtins(cmd, env, 0);
		exit(exit_status);
	}
	execve_wrapper(cmd, env);
	perror("minishell");
	exit(127);
}
