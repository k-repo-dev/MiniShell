#include "../../incls/prototypes.h"

static int	handle_system_errors(t_error_type type);
static int	handle_cd_errors(t_error_type type);
static int	handle_exit_errors(t_error_type type, const char *arg);
static int	handle_unhandled_error(void);

int	handle_error(t_error_type type, const char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	if (type == E_CMD_NOT_FOUND || type == E_EMPTY_CMD)
	{
		if (!arg || !*arg)
			ft_putstr_fd(":command not found\n", 2);
		else
		{
			ft_putstr_fd((char *)arg, 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		return (127);
	}
	if (arg && *arg)
	{
		ft_putstr_fd((char *)arg, 2);
		ft_putstr_fd(": ", 2);
	}
	if (type == E_PERMISSION_DENIED || type == E_SYNTAX_ERROR)
		return (handle_system_errors(type));
	else if (type == E_CD_OLDPWD_UNSET || type == E_CD_TOO_MANY_ARGS)
		return (handle_cd_errors(type));
	else if (type == E_EXIT_TOO_MANY_ARGS || type == E_EXIT_NUMERIC_REQUIRED)
		return (handle_exit_errors(type, arg));
	else
		return (handle_unhandled_error());
}

static int	handle_system_errors(t_error_type type)
{
	if (type == E_PERMISSION_DENIED)
	{
		ft_putstr_fd("Permission denied\n", 2);
		return (126);
	}
	else if (type == E_SYNTAX_ERROR)
	{
		ft_putstr_fd("syntax error\n", 2);
		return (258);
	}
	return (handle_unhandled_error());
}

static int	handle_cd_errors(t_error_type type)
{
	if (type == E_CD_OLDPWD_UNSET)
	{
		ft_putstr_fd("OLDPWD not set\n", 2);
		return (1);
	}
	else if (type == E_CD_TOO_MANY_ARGS)
	{
		ft_putstr_fd("too many arguments\n", 2);
		return (1);
	}
	return (handle_unhandled_error());
}

static int	handle_exit_errors(t_error_type type, const char *arg)
{
	if (type == E_EXIT_TOO_MANY_ARGS)
	{
		ft_putstr_fd("too many arguments\n", 2);
		return (1);
	}
	else if (type == E_EXIT_NUMERIC_REQUIRED)
	{
		ft_putstr_fd((char *)arg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (2);
	}
	return (handle_unhandled_error());
}

static int	handle_unhandled_error(void)
{
	ft_putstr_fd("An unhandled internal error occured\n", 2);
	return (1);
}

int	handle_file_error(const char *filename, const char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd((char *)filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}
