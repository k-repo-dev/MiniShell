#include "../../../incls/prototypes.h"

int	pipeline_fork(t_command *cmd, t_env **env, t_pipe_state *pipe_state)
{
	if (cmd->next && pipe(pipe_state->pipe_fds) == -1)
		return (perror("pipe"), -1);
	*(pipe_state->pid) = fork();
	if (*(pipe_state->pid) == -1)
		return (perror("fork"), -1);
	if (*(pipe_state->pid) == 0)
		child_proc(cmd, env, pipe_state->in_fd, pipe_state->pipe_fds);
	if (pipe_state->in_fd != 0)
		close(pipe_state->in_fd);
	if (cmd->next)
	{
		close(pipe_state->pipe_fds[1]);
		pipe_state->in_fd = pipe_state->pipe_fds[0];
	}
	return (0);
}
