#ifndef EXECUTION_H
# define EXECUTION_H

# include "../libft/libft.h"
# include "minishell.h"
# include "structures.h"

// Execution
void	execve_wrapper(t_command *cmd, t_env **env_list);
int		parent_loop(t_command *cmd_list, t_env **env_list, int last_status);

// Processes
// void	child_proc(t_command *cmd, t_env **env, int in_fd, int *pipe_fds);

// builing Utils
int		handle_builtins(t_command *cmd, t_env **env_list, int last_status);
void	cleanup_redirs(t_command *cmd_list);
void	free_char_array(char **arr);
// int		pipeline_fork(t_command *cmd, t_env **env,
//			t_pipe_state *pipe_state);

// Builtins Parent
int		ft_export(t_command *cmd, t_env **env_list);
int		ft_unset(t_command *cmd, t_env **env_list);
int		ft_cd(t_command *cmd, t_env **env_list);

// Builtins Safe to run in child
int		builtin_echo(t_command *cmd);
int		ft_pwd(void);
int		ft_env(t_env *env_list);
int		ft_exit(t_command *cmd, int last_status);

// Builtin helpers
int		is_numeric(const char *str);

// Pathing
char	*check_absolute_path(const char *cmd);
char	*cmd_findpath(t_env *env);
char	*create_full_path(char *directory, char *cmd);
char	*cmd_path_search(char **paths, char *cmd);
char	*cmd_check(char *cmd, t_env **env);

#endif
