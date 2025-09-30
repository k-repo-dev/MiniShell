#include "../../../incls/prototypes.h"

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
