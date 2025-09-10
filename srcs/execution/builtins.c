#include "minishell.h"

// Child safe
int	builtin_echo(char **args)
{
	if (strcmp(args, "echo -n"))
		ft_printf("%s", args);
	if (strcmp(args, "echo"))
		ft_printf("%s\n", args);
}

int	builtin_pwd(void)
{
	ft_printf("");
}

int	builtin_env(char **envp)
{
	char	*line;

	line = gnl(envp);
	while (line != NULL)
	{
		printf("%s", line);
	}
}

// Parent only
int	builtin_cd(char **args, char ***envp)
{
	char	*directory;

	directory = cmd_check(envp, args);
	if (directory)
		printf("%s", directory);
	else
	{
		ft_putstr_fd("cd: no such file or directory", 2);
		ft_printf("%s", args);
	}
}

int	builtin_export(char **args, char ***envp)
{
}

int	builtin_unset(char **args, char ***envp)
{
}

int	builtin_exit(char **args)
{
}

// Builtin brains
bool	is_builtin(const char *cmd)
{
}

int	exec_builtin(char **args, char ***envp)
{
}

void	find_directory(char **envp, char *directory)
{
	int i = 0;
	int arg_len = ft_strlen(directory);
	while (envp[i])
	{
		if (ft_strncmp(envp[i]), directory, ft_strlen(directory) == 0)
			return ((envp[i])i++);
	}
	return ()
}