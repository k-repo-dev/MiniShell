#ifndef EXECUTION_H
# define EXECUTION_H

# include "../libft/libft.h"
# include "minishell.h"
# include "structures.h"

// Execution
// void	parent_loop(t_command **command_list, char **envp);
// void	child(char **args, char **envp);
// pid_t	fork_wrapper(int pipefd[2]); // currently unused
void	execve_wrapper(t_command *cmd, t_env **env_list);
int		parent_loop(t_command *cmd_list, t_env **env_list, int last_status);

// Builtins
int		builtin_echo(t_command *cmd);
int		handle_builtins(t_command *cmd, t_env **env_list, int last_status);
int		ft_export(t_command *cmd, t_env **env_list);
int		ft_unset(t_command *cmd, t_env **env_list);
int		ft_pwd(void);
int		ft_env(t_env *env_list);
int		ft_cd(t_command *cmd, t_env **env_list);
int		ft_exit(t_command *cmd, int last_status);

// int		builtin_pwd(void);
// int		builtin_env(char **envp);
// int		builtin_cd(t_command *cmd);
// int		builtin_export(t_command *cmd, char **envp);
// int		builtin_unset(t_command *cmd, char **envp);
// bool	is_builtin(const char *cmd);
// void	exec_builtin(t_command **args, char **envp);

// Executables
// char	*is_executable(char *cmd, char **envp);

// Pathing
char	*check_absolute_path(const char *cmd);
char	*cmd_findpath(t_env *env);
char	*create_full_path(char *directory, char *cmd);
char	*cmd_path_search(char **paths, char *cmd);
char	*cmd_check(char *cmd, t_env **env);

// test functions << delete after
// void	test_print(t_command **command_list);

#endif
