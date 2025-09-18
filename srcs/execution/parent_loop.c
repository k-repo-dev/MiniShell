#include "execution.h"
#include "minishell.h"

void	parent_loop(t_command **command_list, char **envp)
{
	int			i;
	t_command	*cmd;
	char		*cmd_path;
	pid_t		pid;
	int			status;
	int			pipe_fd[2];

	i = 0;
	cmd = *command_list;
	printf("\n#####Parent Loop#####");
	printf("\ncmd->args[0]: %s\n", (*command_list)->args[0]);
	printf("cmd->args[1]: %s\n", (*command_list)->args[1]);
	// printf("cmd->args[2]: %s\n", (*command_list)->args[2]);
	// printf("cmd->args[3]: %s\n", (*command_list)->args[3]);
	printf("#####################\n\n\n");
	while (cmd)
	{
		if (cmd->next)
			pipe(pipe_fd);
	}
	if (is_builtin((*command_list)->args[i]) == true)
		exec_builtin(command_list, envp);
	else
	{
		cmd_path = is_executable((*command_list)->args[i], envp);
		if (cmd_path)
		{
			pid = fork();
			if (pid == 0)
				child((*command_list)->args, envp);
			else
				waitpid(pid, &status, 0);
		}
		if (!cmd_path)
			printf("no path\n");
	}
	/*
	after parent runs through all args
	while(wait(&status) > 0);
	to wait for all childs
	//dup2() to redirect stdin/stdout
	//close fds in child and parent
	*/
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
	// else if (ft_strcmp(cmd->args[0], "unset") == 0)
	// 	builtin_unset(cmd, envp);
	// else if (ft_strcmp(cmd, "export") == 0)
	// 	builtin_export(cmd, envp);
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
	perror("execve failed");
	exit(1);
}
