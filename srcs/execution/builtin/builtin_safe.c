#include "../../../incls/prototypes.h"

static void	print_exported_env(t_env *env_list);

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

int	ft_export(t_command *cmd, t_env **env_list)
{
	int		i;
	char	*equals_sign;
	int		exit_status;

	i = 1;
	exit_status = 0;
	if (!cmd->args[i])
	{
		print_exported_env(*env_list);
		return (0);
	}
	while (cmd->args[i])
	{
		equals_sign = ft_strchr(cmd->args[i], '=');
		if (!ft_isalpha(cmd->args[i][0]) && cmd->args[i][0] != '_')
		{
			printf("minishell: export: '%s': not a valid identifier\n", cmd->args[i]);
			exit_status = 1;
		}
		else if (!equals_sign)
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
}

static void	print_exported_env(t_env *env_list)
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
}

int	ft_unset(t_command *cmd, t_env **env_list)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		remove_env_node(env_list, cmd->args[i]);
		i++;
	}
	return (0);
}

int	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
	{
		printf("minishell: pwd: current directory could not be retrived\n");
		return (1);
	}
}

int	ft_env(t_env *env_list)
{
	while (env_list)
	{
		printf("%s=%s\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
	return (0);
}

int	ft_cd(t_command *cmd, t_env **env_list)
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
			return (handle_error(E_CD_OLDPWD_UNSET, NULL));
		printf("%s\n", path);
	}
	else if (cmd->args[2])
		return (handle_error(E_CD_TOO_MANY_ARGS, NULL));
	status = chdir(path);
	if (status == -1)
		return (handle_file_error(path, "No such file or directory"));
	add_env_node(env_list, ft_strdup("OLDPWD"), old_cwd); 
	if (getcwd(old_cwd, sizeof(old_cwd)) != NULL)
		add_env_node(env_list, ft_strdup("PWD"), old_cwd);
	return (0);
}

int	ft_exit(t_command *cmd, int last_status)
{
	(void)last_status;

	printf("exit\n");
	if (cmd->args[1])
	{
		if (cmd->args[2])
			return (handle_error(E_EXIT_TOO_MANY_ARGS, NULL));		
		if (!is_numeric(cmd->args[1]))
			return(handle_error(E_EXIT_NUMERIC_REQUIRED, cmd->args[1]));
		return (-1);
	}
	return (-1);
}

int	is_numeric(const char *str)
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
}
