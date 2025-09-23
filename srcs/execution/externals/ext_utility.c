#include "execution.h"
#include "minishell.h"

char	*is_executable(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;
	char	*result;

	result = check_absolute_path(cmd);
	if (result)
		return (result);
	path_env = (cmd_findpath(envp));
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (free(result), NULL);
	return (cmd_path_search(paths, cmd));
}

void	execve_wrapper(t_command *cmd, char **envp)
{
	char	*cmd_path;

	if (is_builtin(cmd->args[0]))
	{
		child_builtin(&cmd, envp);
		exit(0);
	}
	cmd_path = is_executable(cmd->args[0], envp);
	if (!cmd_path)
	{
		perror("command not found");
		exit(127);
	}
	execve(cmd_path, cmd->args, envp);
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
