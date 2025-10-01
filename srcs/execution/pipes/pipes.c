#include "../../../incls/prototypes.h"

int	execute_pipeline(t_command *cmd, t_env **env)
{
	pid_t			*pids;
	t_pipe_state	pipe_state;
	int				num;
	int				i;
	t_command		*cmd_list_head;

	cmd_list_head = cmd;
	num = count_cmds(cmd);
	pids = malloc(sizeof(pid_t) * num);
	if (!pids)
		return (perror("malloc"), -1);
	pipe_state.in_fd = 0;
	i = 0;
	while (cmd)
	{
		pipe_state.pid = &pids[i];
		if (pipeline_fork(cmd, env, &pipe_state) == -1)
			return (free(pids), -1);
		cmd = cmd->next;
		i++;
	}
	if (pipe_state.in_fd != 0)
		close(pipe_state.in_fd);
	i = wait_all(pids, num);
	cleanup_redirs(cmd_list_head);
	free(pids);
	return (i);
}

int	wait_all(pid_t *pids, int num)
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

int	count_cmds(t_command *cmd_list)
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
