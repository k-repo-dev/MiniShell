#ifndef EXECUTION_H
# define EXECUTION_H

# include "../libft/libft.h"
# include "minishell.h"
# include "structures.h"

// Execution loops
void	parent_loop(t_command **command_list, t_env **env, t_arena *arena);
pid_t	fork_wrapper(int pipefd[2]); // currently unused
void	parent_builtin(t_command **command_list, t_env **env);
void	child_builtin(t_command **args, t_env **env);
void	execve_wrapper(t_command *cmd, t_env **env, t_arena *arena);

// Builtins
int		builtin_echo(t_command *cmd);
int		builtin_pwd(void);
int		builtin_env(t_env *env);
int		builtin_cd(t_command *cmd);
int		builtin_export(t_command *cmd, char **envp);
int		builtin_unset(t_command *cmd, char **envp);
bool	is_builtin(const char *cmd);

// Executables
char	*is_executable(char *cmd, t_env **env);

// execve Pathing
char	*check_absolute_path(const char *cmd);
char	*cmd_findpath(t_env *env);
char	*create_full_path(char *directory, char *cmd);
char	*cmd_path_search(char **paths, char *cmd);
// char	*cmd_check(char *envp[], char *cmd); //redundant

// test functions << delete after
void	test_print(t_command **command_list);

#endif
