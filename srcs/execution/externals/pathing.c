#include "../../../incls/prototypes.h"

char	*check_absolute_path(const char *cmd)
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

char	*cmd_findpath(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->key && ft_strcmp(tmp->key, "PATH") == 0)
			return (tmp->value);
		tmp = tmp->next;
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
			return (full_path);
		if (full_path)
			free(full_path);
		i++;
	}
	return (NULL);
}

char	*cmd_check(char *cmd, t_env **env)
{
	char	*path_env;
	char	**paths;
	char	*result;

	result = check_absolute_path(cmd);
	if (result)
		return (result);
	path_env = cmd_findpath(*env);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	result = cmd_path_search(paths, cmd);
	free_char_array(paths);
	return (result);
}
