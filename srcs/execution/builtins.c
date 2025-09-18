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

int	builtin_pwd(void)
{
	char	*cwd;

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

int	builtin_env(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (1);
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

// Parent only
int	builtin_cd(t_command *cmd)
{
	const char	*target_dir;

	if (cmd->args[1] == NULL)
	{
		target_dir = getenv("HOME");
		if (!target_dir)
		{
			printf("cd: Home not set\n");
			return (1);
		}
	}
	else
	{
		target_dir = cmd->args[1];
	}
	if (chdir(target_dir) != 0)
	{
		printf("cd");
		return (1);
	}
	return (0);
}

// int	builtin_export(t_command *cmd, char **envp)
// {
// 	// char	*new;
// 	// char	*temp;
// 	// sort by ascii
// 	return (0);
// }

// int	builtin_unset(t_command *cmd, char **envp);
