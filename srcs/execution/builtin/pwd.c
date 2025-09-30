#include "../../../incls/prototypes.h"

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
