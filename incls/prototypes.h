#ifndef PROTOTYPES_H
# define PROTOTYPES_H

# include "../libft/libft.h"
# include "minishell.h"
# include "structures.h"

// Function prototypes in signal.c
t_sa		init_sigaction(void (*handler)(int));
void		handle_sigint(int sig);

// Function prototypes from memory_arena.c
void		*alloc_arena(t_arena *arena, size_t size);
int			init_arena(t_arena *arena, size_t size);
char		*arena_strdup(t_arena *arena, const char *str);
void		free_arena(t_arena *arena);
char		*arena_itoa(int n, t_arena *arena);

// Function prortypes from memory_utils.c
size_t		ft_counter(long long n);

// Function prototypes from tokenizer.c
t_token		*tokenizer(const char *line, t_arena *arena);
const char	*find_token_end(const char *start);

// Function prototypes from commands.c
t_command	*parse_commands(t_token *token_head, t_arena *arena);

// Function prortypes from env_vars.c
void		expand_commands(t_command *cmd_list, t_arena *arena, int exit_status);

// Execution
int		parent_loop(t_command args);
pid_t	safe_fork(int pipefd[2]);

// Builtins
int		builtin_echo(char **args);
int		builtin_pwd(void);
int		builtin_env(char **envp);
int		builtin_cd(char **args, char ***envp);
int		builtin_export(char **args, char ***envp);
int		builtin_unset(*char **args, char ***envp);
int		builtin_exit(char **args);
int		is_builtin(const char *cmd);
int		exec_builting(char **args, char ***envp);

// Pathing
char	*cmd_findpath(char *envp[]);
char	*create_full_path(char *directory, char *cmd);
char	*check_absolute_path(char *cmd);
char	*cmd_path_search(char **paths, char *cmd);
char	*cmd_check(char *envp[], char *cmd);

#endif
