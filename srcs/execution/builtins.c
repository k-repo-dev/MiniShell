#include "minishell.h"

// Child safe
int	builtin_echo(char **args);
int	builtin_pwd(void);
int	builtin_env(char **envp);

// Parent only
int	builtin_cd(char **args, char ***envp);
int	builtin_export(char **args, char ***envp);
int	builtin_unset(*char **args, char ***envp);
int	builtin_exit(char **args);

// Builtin brains
int	is_builtin(const char *cmd);
int	exec_builting(char **args, char ***envp);
