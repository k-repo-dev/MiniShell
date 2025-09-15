#include "execution.h"
#include "minishell.h"

// Child safe
int	builtin_echo(t_command *cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	while (cmd->args[1] && strcmp(cmd->args[1], "-n") == 0)
	{
		newline = 0;
		i = 2;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}

int	builtin_pwd(t_command *cmd)
{
	char	*cwd;

	(void)cmd;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

int	builtin_env(t_env *env)
{
	int	i;

	i = 0;
	if (!env || !env->envp)
		return (1);
	while (env->envp[i])
	{
		printf("%s\n", env->envp[i]);
		i++;
	}
	return (0);
}

// Parent only
// int	builtin_cd(t_command **args, char ***envp)
// {
// 	char	*directory;

// 	directory = cmd_check(envp, args);
// 	if (directory)
// 		printf("%s", directory);
// 	else
// 	{
// 		ft_putstr_fd("cd: no such file or directory", 2);
// 		ft_printf("%s", args);
// 	}
// }

// int	builtin_export(t_command **args, char ***envp)
// {
// 	// sort by ascii
// }

// int	builtin_unset(t_command **args, char ***envp)
// {
// }

// Builtin brains
bool	is_builtin(const char *cmd)
{
	if (strcmp(cmd, "echo") == 0 || strcmp(cmd, "pwd") == 0 || strcmp(cmd,
			"env") == 0 || strcmp(cmd, "cd") == 0 || strcmp(cmd, "unset") == 0
		|| strcmp(cmd, "export") == 0 || strcmp(cmd, "exit") == 0)
		return (true);
	else
		return (false);
}

void	exec_builtin(t_command **command_list, t_env *env)
{
	t_command	*cmd;

	cmd = *command_list;
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		builtin_echo(cmd);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
	{
		if (cmd->args[1] == NULL)
			chdir(getenv("HOME"));
		else
			chdir(cmd->args[1]);
	}
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		builtin_pwd(cmd);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		exit(0);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		builtin_env(env);
	// if (args == "pwd")
	// 	buildin_pwd(cmd);
	// if (args == "env")
	// 	buildin_env();
	// if (args == "cd")
	// 	builtin_cd();
	// if (args == "unset")
	// 	builtin_unset();
	// if (args == "export")
	// 	builtin_export();
	// if (args == "exit")
	// 	builtin_exit();
}

// void	find_directory(char **envp, char *directory)
// {
// 	int i = 0;
// 	int arg_len = ft_strlen(directory);
// 	while (envp[i])
// 	{
// 		if (ft_strncmp(envp[i]), directory, ft_strlen(directory) == 0)
// 			return ((envp[i])i++);
// 	}
// 	return (1)
// }