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

char	*arena_itoa(int n, t_arena *arena)
{
	char		*result;
	size_t		len;
	long long	tmp_n;

	tmp_n = (long long)n;
	len = ft_counter(tmp_n);
	result = alloc_arena(arena, len + 1);
	if (result == NULL)
		return (NULL);
	if (tmp_n == 0)
		result[0] = '0';
	if (tmp_n < 0)
	{
		tmp_n *= -1;
		result[0] = '-';
	}
	result[len] = '\0';
	while (len > 0 && tmp_n != 0)
	{
		result[len - 1] = (tmp_n % 10) + '0';
		tmp_n = tmp_n / 10;
		len--;
	}
	return (result);
}
