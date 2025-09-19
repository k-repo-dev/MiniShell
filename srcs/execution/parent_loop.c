#include "execution.h"
#include "minishell.h"

void	parent_loop(t_command **command_list, char **envp)
{
	t_command	*cmd;
	pid_t		pid;
	int			status;
	int			pipe_fd[2];
	int			prev_fd;

	prev_fd = -1;
	cmd = *command_list;
	test_print(command_list);
	while (cmd)
	{
		if (cmd->next)
			pipe(pipe_fd);
		pid = fork();
		if (pid == 0) // Child process
		{
			if (prev_fd != -1)
				dup2(prev_fd, STDIN_FILENO);
			if (cmd->next)
				dup2(pipe_fd[1], STDOUT_FILENO);
			if (prev_fd != -1)
				close(prev_fd);
			if (cmd->next)
			{
				close(pipe_fd[0]);
				close(pipe_fd[1]);
			}
			execve_wrapper(cmd, envp);
			exit(1);
		}
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		cmd = cmd->next;
	}
	while (wait(&status) > 0)
		;
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
	// cd parent only
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		builtin_cd(cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return ;
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		builtin_env(envp);
	// else if (ft_strcmp(cmd->args[0], "unset") == 0)
	// 	builtin_unset(cmd, envp);
	// else if (ft_strcmp(cmd, "export") == 0)
	// 	builtin_export(cmd, envp);
}
