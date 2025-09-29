#include "../../../incls/prototypes.h"

void	handle_single_quote(const char **str, char **expand_str)
{
	(*str)++;
	while (**str && **str != '\'')
		*(*expand_str)++ = *(*str)++;
	if (**str == '\'')
		(*str)++;
}

void	handle_double_quote(const char **str, char **expand_str, int exit_status, t_env *env_list)
{
	(*str)++;
	while (**str && **str != '"')
	{
		if (**str == '$' && is_expand_char(*(*str + 1)))
			handle_var_expand(str, expand_str, exit_status, env_list);
		else
			copy_char(str, expand_str);
	}
	if (**str == '"')
		(*str)++;
}

void	handle_var_expand(const char **str, char **expand_str, int exit_status, t_env *env_list)
{
	const char	*value;
	char		*tmp_value;

	value = NULL;
	tmp_value = NULL;
	(*str)++;
	if (**str == '?')
	{
		tmp_value = ft_itoa(exit_status);
		value = tmp_value;
		while (*value)
			*(*expand_str)++ = *value++;
		free(tmp_value);
		(*str)++;
	}
	else
		expand_normal_var(str, expand_str, env_list);
}

void	copy_value_to_expand(const char *value, char **expand_str)
{
	while (*value)
		*(*expand_str)++ = *value++;
}

void	expand_normal_var(const char **str, char **expand_str, t_env *env_list)
{
	const char	*start;
	const char	*value;
	char		var_name[256];
	size_t		len;

	start = *str;
	value = NULL;
	while (**str && (ft_isalnum(**str) || **str == '_'))
		(*str)++;
	len = *str - start;
	if (len >= 256)
		return ;
	ft_strlcpy(var_name, start, len + 1);
	value = get_env_value(env_list, var_name);
	if (value)
		copy_value_to_expand(value, expand_str);
}
