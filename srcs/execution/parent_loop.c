#include "execution.h"
#include "minishell.h"

int	parent_loop(t_command **command_list, char **envp)
{
	int			i;
	t_command	*cmd;
	char		*cmd_path;
	pid_t		pid;
	int			fd[2];

	// int			status;
	i = 0;
	cmd = *command_list;
	// int	fd[2];
	// check for builtin or binary
	printf("\n#####Parent Loop#####");
	printf("\ncmd->args[0]: %s\n", (*command_list)->args[0]);
	printf("cmd->args[1]: %s\n", (*command_list)->args[1]);
	// printf("cmd->args[2]: %s\n", (*command_list)->args[2]);
	// printf("cmd->args[3]: %s\n", (*command_list)->args[3]);
	printf("#####################\n\n\n");
	if (is_builtin((*command_list)->args[0]) == true)
		exec_builtin(command_list, envp);
	cmd_path = is_executable((*command_list)->args[0], envp);
	if (cmd_path)
	{
		pid = safe_fork(fd);
		if (pid == 0)
		{
			child((*command_list)->args, envp);
			waitpid(pid, NULL, 0);
			// WEXITSTATUS(status);
		}
	}
	close(fd[0]);
	close(fd[1]);
	if (!cmd_path)
		printf("no path\n");
	return (0);
	// *cmd_check(*envp, args->arg[args]);
	// safe_fork(NULL);
}

// Builtin brains
bool	is_builtin(const char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (true);
	else
		return (false);
}
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

void	exec_builtin(t_command **command_list, char **envp)
{
	t_command	*cmd;

	cmd = *command_list;
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		builtin_echo(cmd);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		builtin_cd(cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return ;
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		builtin_env(envp);
	// if (args == "unset")
	// 	builtin_unset();
	// if (args == "export")
	// 	builtin_export();
}

void	child(char **args, char **envp)
{
	char	*cmd_path;

	printf("\n#####Child######\n");
	if (!args)
	{
		printf("big rip\n");
		return ;
	}
	printf("child arg: %s\n", args[0]);
	cmd_path = is_executable(*args, envp);
	execve(cmd_path, &args[0], envp);
	perror("execve");
	return ;
}

// int	not_main(int argc, char *argv[], char *envp[])
// {
// 	int		pipefd[2];
// 	pid_t	pid1;
// 	pid_t	pid2;
// 	int		status1;
// 	int		status2;

// 	if (argc != 5)
// 		cmd_error_msg("Usage: ./pipex file1 cmd1 cmd2 file2\n", 1);
// 	if (pipe(pipefd) < 0)
// 		bad_pipe("pipe");
// 	pid1 = safe_fork(pipefd);
// 	if (pid1 == 0)
// 		kid_one(argv, envp, pipefd);
// 	pid2 = safe_fork(pipefd);
// 	if (pid2 == 0)
// 		kid_two(argv, envp, pipefd);
// 	close(pipefd[0]);
// 	close(pipefd[1]);
// 	waitpid(pid1, &status1, 0);
// 	waitpid(pid2, &status2, 0);
// 	if (WIFEXITED(status2))
// 		return (WEXITSTATUS(status2));
// 	return (1);
// }
