#ifndef EXECUTION_H
# define EXECUTION_H

# include "../libft/libft.h"
# include "minishell.h"
# include "structures.h"

// Execution
void	execve_wrapper(t_command *cmd, t_env **env_list);

// Processes
void	child_proc(t_command *cmd, t_env **env, int in_fd, int *pipe_fds);
int		parent_loop(t_command *cmd_list, t_env **env_list, int last_status);
int		is_parent_builtin(const char *cmd);

// Builtin Utils
int		handle_builtins(t_command *cmd, t_env **env_list, int last_status);
void	cleanup_redirs(t_command *cmd_list);
void	free_char_array(char **arr);
int		is_builtin(const char *cmd);

// Builtins Parent
int		ft_export(t_command *cmd, t_env **env_list);
int		ft_unset(t_command *cmd, t_env **env_list);
int		ft_cd(t_command *cmd, t_env **env_list);

// Builtins Safe to run in child
int		builtin_echo(t_command *cmd);
int		ft_pwd(void);
int		ft_env(t_command *cmd, t_env *env_list);
int		ft_exit(t_command *cmd, int last_status);

// Builtin helpers
int		is_numeric(const char *str);
void	print_exported_env(t_env *env_list);
int		count_cmds(t_command *cmd_list);
t_env	**stack_to_array(t_env *env_list, int size);
void	bubble_sort(t_env **array, int size);
int		ft_listsize(t_env *list);

// Pipes & Redirections
int		execute_pipeline(t_command *md_list, t_env **env_list);
int		handle_redirs(t_redir *redirs);
int		pipeline_fork(t_command *cmd, t_env **env, t_pipe_state *pipe_state);
int		wait_all(pid_t *pids, int num);

// Pathing
char	*check_absolute_path(const char *cmd);
char	*cmd_findpath(t_env *env);
char	*create_full_path(char *directory, char *cmd);
char	*cmd_path_search(char **paths, char *cmd);
char	*cmd_check(char *cmd, t_env **env);

#endif
