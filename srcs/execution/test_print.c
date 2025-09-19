#include "execution.h"
#include "minishell.h"

void	test_print(t_command **command_list)
{
	int			i;
	t_command	*cmd;

	i = 0;
	cmd = *command_list;
	while (cmd)
	{
		printf("\n##### Commands #####\n");
		// i = 0;
		while (cmd->args && cmd->args[i])
		{
			printf("arg[%d]: %s\n", i, cmd->args[i]);
			i++;
		}
		// printf("####################\n\n");
		cmd = cmd->next;
	}
}
