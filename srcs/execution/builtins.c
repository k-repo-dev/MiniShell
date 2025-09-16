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
	while (cmd->args[i] && strcmp(cmd->args[i], "-n") == 0)
	{
		newline = 0;
		i++;
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
// int	builtin_cd(t_command **args)
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