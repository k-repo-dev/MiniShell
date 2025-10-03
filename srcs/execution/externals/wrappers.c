#include "../../../incls/prototypes.h"

void	execve_wrapper(t_command *cmd, t_env **env_list)
{
	char	*cmd_path;
	char	**envp;
	int		exit_code;
	char	*cmd_name;

	cmd_name = cmd->args[0];
	envp = env_list_to_array(*env_list);
	if (!envp)
		exit(1);
	cmd_path = cmd_check(cmd->args[0], env_list);
	if (!cmd_path)
	{
		if (ft_strchr(cmd_name, '/') != NULL || cmd_name[0] == '.')
		{
			if (errno == ENOENT)
				exit_code = handle_file_error(cmd_name, "No such file or directory");
			else if (errno == EACCES)
				exit_code = handle_file_error(cmd_name, "Permission denied");
			else
				exit_code = handle_file_error(cmd_name, strerror(errno));
		}
		else
			exit_code = handle_error(E_CMD_NOT_FOUND, cmd->args[0]);
		free_char_array(envp);
		exit(exit_code);
	}
	execve(cmd_path, cmd->args, envp);
	if (errno == EACCES)
		exit_code = handle_error(E_PERMISSION_DENIED, cmd->args[0]);
	else
		exit_code = handle_file_error(cmd->args[0], strerror(errno));
	free_char_array(envp);
	exit(exit_code);
}

void	free_char_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
