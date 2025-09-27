#include "../../incls/prototypes.h"

int	handle_error(t_error_type type, const char *arg)
{
	int	exit_code;

	printf("minishell: ");
	if (arg && *arg)
		printf("%s: ", arg);
	if (type == E_EMPTY_CMD)
	{
		printf(":command not found\n");
		exit_code = 127;
	}
	else if (type == E_CMD_NOT_FOUND)
	{
		printf("command not found\n");
		exit_code = 127;
	}
	else if (type == E_PERMISSION_DENIED)
	{
		printf("Permission denied\n");
		exit_code = 126;
	}
	else if (type == E_SYNTAX_ERROR)
	{
		printf("syntax error\n");
		exit_code = 258;
	}
	else if (type == E_CD_OLDPWD_UNSET)
	{
		printf("OLDPWD not set\n");
		exit_code = 1;
	}
	else if (type == E_CD_TOO_MANY_ARGS)
	{
		printf("too many arguments\n");
		exit_code = 1;
	}
	else if (type == E_EXIT_TOO_MANY_ARGS)
	{
		printf("too many arguments\n");
		exit_code = 1;
	}
	else if (type == E_EXIT_NUMERIC_REQUIRED)
	{
		printf("%s: numeric argument required\n", arg);
		exit_code = 2;
	}
	else
	{
		printf("An unhandled internal error occured\n");
		exit_code = 1;
	}
	return (exit_code);
}

int	handle_file_error(const char *filename, const char *msg)
{
	printf("minishell: %s: %s\n", filename, msg);
	return (1);
}
