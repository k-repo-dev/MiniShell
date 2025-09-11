#ifndef EXECUTION_H
# define EXECUTION_H

# include "../libft/libft.h"
# include "minishell.h"
# include "structures.h"

// Execution
int		parent_loop(t_command args, char **envp);
pid_t	safe_fork(int pipefd[2]);

// Builtins
int		builtin_echo(t_command **args);
int		builtin_pwd(void);
int		builtin_env(char **envp);
int		builtin_cd(t_command **args, char ***envp);
int		builtin_export(t_command **args, char ***envp);
int		builtin_unset(t_command **args, char ***envp);
int		builtin_exit(t_command **args);
bool	is_builtin(const char *cmd);
int		exec_builtin(t_command **args, char ***envp);

// Pathing
char	*cmd_findpath(char *envp[]);
char	*create_full_path(char *directory, char *cmd);
char	*check_absolute_path(char *cmd);
char	*cmd_path_search(char **paths, char *cmd);
char	*cmd_check(char *envp[], char *cmd);

#endif
