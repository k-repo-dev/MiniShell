// #include "../../../incls/prototypes.h"

// static void	child_proc(t_command *cmd, t_env **env, int in_fd,
//		int *pipe_fds)
// {
// 	int	exit_status;

// 	if (in_fd != 0)
// 	{
// 		dup2(in_fd, STDIN_FILENO);
// 		close(in_fd);
// 	}
// 	if (cmd->next)
// 	{
// 		dup2(pipe_fds[1], STDOUT_FILENO);
// 		close(pipe_fds[0]);
// 		close(pipe_fds[1]);
// 	}
// 	handle_redirs(cmd->redirs);
// 	if (is_builtin(cmd->args[0]))
// 	{
// 		exit_status = handle_builtins(cmd, env, 0);
// 		exit(exit_status);
// 	}
// 	execve_wrapper(cmd, env);
// 	perror("minishell");
// 	exit(127);
// }

// static int	pipeline_fork(t_command *cmd, t_env **env,
//		t_pipe_state *pipe_state)
// {
// 	if (cmd->next && pipe(pipe_state->pipe_fds) == -1)
// 		return (perror("pipe"), -1);
// 	*(pipe_state->pid) = fork();
// 	if (*(pipe_state->pid) == -1)
// 		return (perror("fork"), -1);
// 	if (*(pipe_state->pid) == 0)
// 		child_proc(cmd, env, pipe_state->in_fd, pipe_state->pipe_fds);
// 	if (pipe_state->in_fd != 0)
// 		close(pipe_state->in_fd);
// 	if (cmd->next)
// 	{
// 		close(pipe_state->pipe_fds[1]);
// 		pipe_state->in_fd = pipe_state->pipe_fds[0];
// 	}
// 	return (0);
// }

// static int	wait_all(pid_t *pids, int num)
// {
// 	int	status;
// 	int	i;

// 	i = 0;
// 	while (i < num)
// 	{
// 		waitpid(pids[i], &status, 0);
// 		i++;
// 	}
// 	return (WEXITSTATUS(status));
// }

// static int	execute_pipeline(t_command *cmd, t_env **env)
// {
// 	pid_t			*pids;
// 	t_pipe_state	pipe_state;
// 	int				num;
// 	int				i;
// 	t_command		*cmd_list_head;

// 	num = count_cmds(cmd);
// 	pids = malloc(sizeof(pid_t) * num);
// 	if (!pids)
// 		return (perror("malloc"), -1);
// 	pipe_state.in_fd = 0;
// 	i = 0;
// 	while (cmd)
// 	{
// 		pipe_state.pid = &pids[i];
// 		if (pipeline_fork(cmd, env, &pipe_state) == -1)
// 			return (free(pids), -1);
// 		cmd = cmd->next;
// 		i++;
// 	}
// 	if (pipe_state.in_fd != 0)
// 		close(pipe_state.in_fd);
// 	i = wait_all(pids, num);
// 	cleanup_redirs(cmd_list_head);
// 	free(pids);
// 	return (i);
// }
