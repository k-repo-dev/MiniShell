#include "../../../incls/prototypes.h"

int	handle_builtins(t_command *cmd, t_env **env_list, int last_status)
{
	//DEBUG START
	int arg_count = 0;
	while (cmd->args[arg_count] != NULL)
		arg_count++;
	printf("DEBUG HB-1: Executing builtin '%s'. Arg count: %d\n", cmd->args[0], arg_count);
	for (int i = 0; cmd->args[i] != NULL; i++)
		printf("DEBUG HB-2: Processing Arg[%d]: '%s'\n", i, cmd->args[i]);
	//DEBUG END
	if (!cmd->args[0])
		return (0);
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (builtin_echo(cmd));
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (ft_cd(cmd, env_list));
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (ft_export(cmd, env_list));
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (ft_unset(cmd, env_list));
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (ft_env(*env_list));
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (ft_exit(cmd, last_status));
	return (1);
}
