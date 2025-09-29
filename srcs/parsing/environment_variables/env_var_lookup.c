#include "../../../incls/prototypes.h"

char	*get_variable_value(const char *var_name, int exit_status, t_arena *arena)
{
	const char	*value;

	value = NULL;
	if (var_name && var_name[0] == '?' && !var_name[1])
	{
		if (arena == NULL)
			return (ft_itoa(exit_status));
		return (arena_itoa(exit_status, arena));
	}
	value = getenv(var_name);
	if (!value)
		return (NULL);
	if (arena == NULL)
		return (ft_strdup(value));
	return (arena_strdup(arena, value));
}

int	is_expand_char(char c)
{
	return (ft_isalnum(c) || c == '?');
}
