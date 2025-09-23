#include "../../incls/prototypes.h"

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

/*int	handle_builtins(t_command *cmd, t_env **env_list)
{
	if (!cmd->args[0])
		return (0);
	if (ft_strcmp(cmd->args[0]. "echo") == 0)
		return (builtin_echo);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (ft_cd(cmd, env_list));
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(cmd->rgs[0], "export") == 0)
		return (ft_export(cmd, env_list));
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (ft_unset(cmd, env_list));
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (ft_env(*env_list));
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (ft_exit(cmd));
	return (1);
}*/

/*int	ft_export(t_command *cmd, t_env **env_list)
{
	int		i;
	char	*equals_sign;
	int		exit_status;

	i  = 1;
	exit_status = 0;
	if (!cmd->args[i])
	{
		print_exported_env(*env_list);
		return (0);
	}
	while (cmd->args[i])
	{
		equals_sign = ft_strchr(cmd->args[i], '=');
		if (!equals_sign)
		{
			if (get_env_value(*env_list, cmd->args[i]) == NULL)
				add_env_node(env_list, cmd->args[i], NULL);
		}
		else
		{
			*equals_sign = '\0';
			add_env_node(env_list, cmd->args[i], equals_sign + 1);
		}
		i++;
	}
	return (exit_status);
}*/

/*static void	print_exported_env(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		printf("declare -x %s", current->key);
		if (current->value)
			printf("=\"%s\"", current->value);
		printf("\n");
		current = current->next;
	}
}*/

/*int	ft_unset(t_command *cmd, t_env **env_list)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		remove_env_node(env_list, cmd->args[i]);
		i++;
	}
	return (0);
}*/

/*int	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
	{
		perror("minishell: pwd");
		return (1);
	}
}*/

/*int	ft_env(t_env *envlist)
{
	while (env_list)
	{
		printf("%s=%s\n", env_list->key, env_list->value);
		env_list =env_list->next;
	}
	return (0);
}*/

/*int	fd_cd(t_command *cmd, t_env **env_list)
{
	char	old_cwd[1024];
	char	*path;
	int		status;
	if (getcwd(old_cwd, sizeof(old_cwd)) == NULL)
		return (1);
	path = cmd->args[1];
	if (!path || ft_strcmp(path, "~") == 0)
		path = get_env_value(*env_list, "HOME");
	else if (ft_strcmp(path, "-") == 0)
	{
		path = get_env_value(*env_list, "OLDPWD");
		if (!path)
		{
			printf("minishell: cd: OLDPWD nor set\n");
		return (1);
		}
		printf("%s\n", path);
	}
	else if (cmd->args[2])
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	status = chdir(path);
	if (status == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	add_env_node(env_list, ft_strdup("OLDPWD"), old_cwd);
	if (getcwd(old_cwd, sizeof(old_cwd)) != NULL)
		add_env_node(env_list, ft_strdup("PWD"), old_cwd);
	return (0);
}*/

//static int	is_numeric(const char *str);

/*int	ft_exit(t_command *cmd, int last_status)
{
	long	status;

	printf("exit\n");
	if (cmd->args[1])
	{
		if (cmd->args[2])
		{
			printf("minishell: exit: too many arguments\n");
			return (1);
		}
		if (!is_numeric(cmd->args[1]))
		{
			printf("minishell: exit: %s: numeric argument required\n", cmd->args[1]);
			exit(2);
		}
		status = ft_atoi(cmd->args[1]);
		exit(status);
	}
	exit(last_status);
	return (0);
}*/

/*static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}*/
