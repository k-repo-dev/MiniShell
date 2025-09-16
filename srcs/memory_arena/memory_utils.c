#include "../../incls/prototypes.h"

size_t	ft_counter(long long n)
{
	size_t	len;

	len = 0;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n > 9)
	{
		n = n / 10;
		len++;
	}
	len++;
	return (len);
}

char	*arena_strndup(t_arena *arena, const char *s1, size_t n)
{
	char	*str;
	size_t	i;

	str = alloc_arena(arena, n +1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < n)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
