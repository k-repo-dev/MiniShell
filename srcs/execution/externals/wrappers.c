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

	envp = env_list_to_array(*env_list);
	if (!envp)
		exit(1);
	cmd_path = cmd_check(cmd->args[0], env_list);
	if (!cmd_path)
	{
		free_char_array(envp);
		exit(127);
	}
	execve(cmd_path, cmd->args, envp);
	free_char_array(envp);
	if (errno == EACCES)
		exit(126);
	else
		exit(127);
}

void	free_char_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
