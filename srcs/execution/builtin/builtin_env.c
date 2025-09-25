#include "../../../incls/prototypes.h"

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

// sort by ascii
// int	builtin_export(t_command *cmd, t_env **envp)
// {
// 	int	i;

// 	i = 1;
// 	if (!cmd->args[1])
// 		add_env_node(env);
// 	return (0);
// }

// // int	builtin_unset(t_command *cmd, char **envp);

// void	print_export(t_env *env)
// {
// 	while (env)
// 	{
// 		// ordered by ascii
// 		printf("%s", env->value);
// 		env = env->next;
// 	}
// }
