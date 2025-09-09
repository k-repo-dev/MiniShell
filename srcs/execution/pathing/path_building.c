#include "minishell.h"

char	*cmd_findpath(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*create_full_path(char *directory, char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(directory, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	if (!full_path)
		return (NULL);
	return (full_path);
}

char	*check_absolute_path(char *cmd)
{
	if (!cmd)
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (NULL);
}

char	*cmd_path_search(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	if (!cmd)
		return (NULL);
	while (paths[i])
	{
		full_path = create_full_path(paths[i], cmd);
		if (full_path && access(full_path, X_OK) == 0)
		{
			cmd_freeargs(paths);
			return (full_path);
		}
		if (full_path)
			free(full_path);
		i++;
	}
	cmd_freeargs(paths);
	return (NULL);
}

char	*cmd_check(char *envp[], char *cmd)
{
	char	*path_env;
	char	**paths;
	char	*result;

	result = check_absolute_path(cmd);
	if (result)
		return (result);
	path_env = (cmd_findpath(envp));
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (free(result), NULL);
	return (cmd_path_search(paths, cmd));
}
