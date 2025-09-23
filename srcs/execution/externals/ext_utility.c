#include "prototypes.h"

char	*is_executable(char *cmd, t_env **env)
{
	char	*path_env;
	char	**paths;
	char	*result;

	result = check_absolute_path(cmd);
	if (result)
		return (result);
	path_env = (cmd_findpath(*env));
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (free(result), NULL);
	return (cmd_path_search(paths, cmd));
}

void	execve_wrapper(t_command *cmd, t_env **env, t_arena *arena)
{
	char	*cmd_path;
	char	**envp_array;

	if (is_builtin(cmd->args[0]))
	{
		child_builtin(&cmd, env);
		exit(0);
	}
	cmd_path = is_executable(cmd->args[0], env);
	if (!cmd_path)
	{
		perror("command not found");
		exit(127);
	}
	envp_array = env_list_to_array(*env, arena);
	if (!envp_array)
	{
		perror("envp array failed");
		exit(1);
	}
	execve(cmd_path, cmd->args, envp_array);
	perror("execve failed");
	exit(1);
}

// unused
pid_t	fork_wrapper(int pipefd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		perror("fork");
		exit(1);
	}
	return (pid);
}
