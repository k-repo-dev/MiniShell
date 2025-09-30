#include "../../../incls/prototypes.h"

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
			return (handle_error(E_CD_OLDPWD_UNSET, "cd"));
		printf("%s\n", path);
	}
	else if (cmd->args[2])
		return (handle_error(E_CD_TOO_MANY_ARGS, "cd"));
	status = chdir(path);
	if (status == -1)
		return (handle_file_error(path, "No such file or directory"));
	add_env_node(env_list, ft_strdup("OLDPWD"), old_cwd);
	if (getcwd(old_cwd, sizeof(old_cwd)) != NULL)
		add_env_node(env_list, ft_strdup("PWD"), old_cwd);
	return (0);
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
