#include "../../../incls/prototypes.h"

void	execve_wrapper(t_command *cmd, t_env **env_list)
{
	char	*cmd_path;
	char	**envp;

	int exit_code; // part of test
	envp = env_list_to_array(*env_list);
	if (!envp)
		exit(1);
	cmd_path = cmd_check(cmd->args[0], env_list);
	if (!cmd_path)
	{
		// testing solution
		exit_code = handle_error(E_CMD_NOT_FOUND, cmd->args[0]); // part of test
		free_char_array(envp);
		// exit(127);
		exit(exit_code); // part of test
	}
	execve(cmd_path, cmd->args, envp);
	// free_char_array(envp);
	if (errno == EACCES)
		exit_code = handle_error(E_PERMISSION_DENIED, cmd->args[0]);
			// part of test
																		// exit(126);
	else
		exit_code = handle_file_error(cmd->args[0], strerror(errno));
			// part of test
																		// exit(127);
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
