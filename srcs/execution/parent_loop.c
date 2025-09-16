#include "execution.h"
#include "minishell.h"

int	parent_loop(t_command **command_list, char **envp)
{
	t_env	*env;

	env = NULL;
	// int	fd[2];
	// check for builtin or binary
	printf("\n#####Parent Loop#####");
	printf("\ncmd->args[0]: %s\n", (*command_list)->args[0]);
	printf("cmd->args[1]: %s\n", (*command_list)->args[1]);
	// printf("cmd->args[2]: %s\n", (*command_list)->args[2]);
	// printf("cmd->args[3]: %s\n", (*command_list)->args[3]);
	printf("\n\n\n\n\n\n");
	if (is_builtin((*command_list)->args[0]) == true)
		exec_builtin(command_list, envp);
	// *cmd_check(*envp, args->arg[args]);
	// safe_fork(NULL);
	return (0);
}

// Builtin brains
bool	is_builtin(const char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (true);
	else
		return (false);
}

void	exec_builtin(t_command **command_list, char **envp)
{
	t_command	*cmd;

	cmd = *command_list;
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		builtin_echo(cmd);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		builtin_cd(cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return ;
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		builtin_env(envp);
	// if (args == "unset")
	// 	builtin_unset();
	// if (args == "export")
	// 	builtin_export();
}

// int	not_main(int argc, char *argv[], char *envp[])
// {
// 	int		pipefd[2];
// 	pid_t	pid1;
// 	pid_t	pid2;
// 	int		status1;
// 	int		status2;

// 	if (argc != 5)
// 		cmd_error_msg("Usage: ./pipex file1 cmd1 cmd2 file2\n", 1);
// 	if (pipe(pipefd) < 0)
// 		bad_pipe("pipe");
// 	pid1 = safe_fork(pipefd);
// 	if (pid1 == 0)
// 		kid_one(argv, envp, pipefd);
// 	pid2 = safe_fork(pipefd);
// 	if (pid2 == 0)
// 		kid_two(argv, envp, pipefd);
// 	close(pipefd[0]);
// 	close(pipefd[1]);
// 	waitpid(pid1, &status1, 0);
// 	waitpid(pid2, &status2, 0);
// 	if (WIFEXITED(status2))
// 		return (WEXITSTATUS(status2));
// 	return (1);
// }

// void	child(char *argv[], char *envp[], int *pipefd)
// {
// 	int		infile;
// 	char	*cmd_path;
// 	char	**cmd_args;

// 	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
// 		bad_dup("dup2", 1);
// 	close(pipefd[0]);
// 	close(pipefd[1]);
// 	cmd_args = cmd_parse(argv[2]);
// 	if (!cmd_args)
// 		cleanup_and_exit(NULL, NULL, 127);
// 	cmd_path = cmd_check(envp, cmd_args[0]);
// 	if (!cmd_path)
// 		no_path(cmd_args, 127);
// 	infile = open(argv[1], O_RDONLY);
// 	if (infile == -1)
// 		no_infile(argv[1], cmd_args, cmd_path, 1);
// 	if (dup2(infile, STDIN_FILENO) == -1)
// 		bad_dup("dup2", 1);
// 	close(infile);
// 	execve(cmd_path, cmd_args, envp);
// 	perror("execve");
// 	cleanup_and_exit(cmd_args, cmd_path, 1);
// }
