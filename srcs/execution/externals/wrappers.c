#include "../../incls/prototypes.h"

// pid_t	fork_wrapper(int pipefd[2])
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		close(pipefd[0]);
// 		close(pipefd[1]);
// 		perror("fork");
// 		exit(1);
// 	}
// 	return (pid);
// }

void	execve_wrapper(t_command *cmd, t_env **env_list)
{
	char	*cmd_path;
	char	**envp;
	t_arena	arena;

	init_arena(&arena, 4096);
	envp = env_list_to_array(*env_list, &arena);
	cmd_path = cmd_check(cmd->args[0], env_list);
	if (!cmd_path)
		exit(handle_error(E_CMD_NOT_FOUND, cmd->args[0]));
	execve(cmd_path, cmd->args, envp);
	if (errno == EACCES)
		exit(handle_error(E_PERMISSION_DENIED, cmd->args[0]));
	else
		exit(handle_error(E_CMD_NOT_FOUND, cmd->args[0]));
}
