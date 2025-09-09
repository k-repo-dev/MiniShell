#include "minishell.h"

// Child safe
int	builtin_echo(char **args)
{
	if (strcmp(args, "-n"))
		ft_printf("%s", args);
	else
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
	if (args)
	{
	}
	else
	{
		ft_putstr("cd: no such file or directory" 2);
		ft_printf("%s", arg);
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
