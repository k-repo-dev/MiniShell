#ifndef EXECUTION_H
# define EXECUTION_H

# include "../libft/libft.h"
# include "minishell.h"
# include "structures.h"

// Execution
int		parent_loop(t_command **command_list, char **envp);
// int		child(t_command args, t_command **env);
pid_t	safe_fork(int pipefd[2]);

// Builtins
int		builtin_echo(t_command *cmd);
int		builtin_pwd(void);
int		builtin_env(char **envp);
int		builtin_cd(t_command *cmd);
// int		builtin_export(t_command **args, char ***envp);
// int		builtin_unset(t_command **args, char ***envp);
bool	is_builtin(const char *cmd);
void	exec_builtin(t_command **args, char **envp);

// Executables

// Pathing
// char	*cmd_findpath(char *envp[]);
// char	*create_full_path(char *directory, char *cmd);
char	*check_absolute_path(const char *cmd);
// char	*cmd_path_search(char **paths, char *cmd);
// char	*cmd_check(char *envp[], char *cmd);

#endif
