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
	exit_status = handle_redirs(cmd->redirs);
	if (exit_status != 0)
		exit(exit_status);
	if (cmd->args && cmd->args[0] && is_builtin(cmd->args[0]))
	{
		exit_status = handle_builtins(cmd, env, 0);
		exit(exit_status);
	}
	execve_wrapper(cmd, env);
	handle_error(E_CMD_NOT_FOUND, cmd->args[0]);
	// perror("minishell");
	// exit(127);
}
