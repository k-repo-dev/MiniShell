/*#include "execution.h"
#include "minishell.h"

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

void	execve_wrapper(t_command *cmd, char **envp)
{
	char	*cmd_path;

	if (is_builtin(cmd->args[0]))
	{
		exec_builtin(&cmd, envp);
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
}*/
