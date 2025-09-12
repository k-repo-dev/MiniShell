#include "execution.h"
#include "minishell.h"

// Child safe
int	builtin_echo(t_command **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (!args || !args[0])
		return (1);
	while (args[i] && strcmp(args[i], "-n" != 0))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}

int	builtin_pwd(t_command **args)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
	}
	else
	{
		printf("Current directory: %s\n", cwd);
	}
}

int	builtin_env(char **envp)
{
	char	*line;

	line = gnl(envp);
	while (line != NULL)
	{
		printf("%s", line);
	}
}

// Parent only
int	builtin_cd(t_command **args, char ***envp)
{
	char	*directory;

	directory = cmd_check(envp, args);
	if (directory)
		printf("%s", directory);
	else
	{
		ft_putstr_fd("cd: no such file or directory", 2);
		ft_printf("%s", args);
	}
}

int	builtin_export(t_command **args, char ***envp)
{
	// sort by ascii
}

int	builtin_unset(t_command **args, char ***envp)
{
}

// Builtin brains
bool	is_builtin(const char *cmd)
{
	if (cmd == "echo" || cmd == "pwd" || cmd == "env" || cmd == "cd"
		|| cmd == "unset" || cmd == "export" || cmd == "exit")
		return (true);
	else
		return (false);
}

void	exec_builtin(t_command *command_list, char ***envp)
{
	// check if parent or child friendly?
	if (ft_strcmp(command_list->args[0], "echo") == 0)
		builtin_echo(command_list->args);
	if (ft_strcmp(command_list->args[0], "cd") == 0)
		if (command_list->args[1] == NULL)
			chdir(getenv("HOME"));
		else
			chdir(command_list->args[1]);
	else if (ft_strcmp(command_list->args, "exit") == 0)
		exit(0);
	// if (args == "pwd")
	// 	buildin_pwd();
	// if (args == "env")
	// 	buildin_env();
	// if (args == "cd")
	// 	builtin_cd();
	// if (args == "unset")
	// 	builtin_unset();
	// if (args == "export")
	// 	builtin_export();
	// if (args == "exit")
	// 	builtin_exit();
}

// void	find_directory(char **envp, char *directory)
// {
// 	int i = 0;
// 	int arg_len = ft_strlen(directory);
// 	while (envp[i])
// 	{
// 		if (ft_strncmp(envp[i]), directory, ft_strlen(directory) == 0)
// 			return ((envp[i])i++);
// 	}
// 	return (1)
// }