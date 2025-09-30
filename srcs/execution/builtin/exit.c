#include "../../../incls/prototypes.h"

int	ft_exit(t_command *cmd, int last_status)
{
	(void)last_status;
	printf("exit\n");
	if (cmd->args[1])
	{
		if (cmd->args[2])
			return (handle_error(E_EXIT_TOO_MANY_ARGS, "exit"));
		if (!is_numeric(cmd->args[1]))
			return (handle_error(E_EXIT_NUMERIC_REQUIRED, cmd->args[1]));
		return (-1);
	}
	return (-1);
}
