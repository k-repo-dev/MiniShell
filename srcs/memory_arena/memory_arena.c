#include "../../incls/prototypes.h"

int	init_arena(t_arena *arena, size_t size)
{
	if (arena == NULL || size == 0)
	{
		//ft_putstr_fd(ARENA_ERR, 2);
		return (-1);
	}
	arena->buffer = (char *)malloc(size);
	if (arena->buffer == NULL)
	{
		//ft_putstr_fd(ALLOC_ERR, 2);
		return (-1);
	}
	arena->size = size;
	arena->offset = 0;
	return (0);
}

void	*alloc_arena(t_arena *arena, size_t size)
{
	void	*ptr;

	if (arena->offset + size > arena->size)
		return (NULL);
	ptr = arena->buffer + arena->offset;
	arena->offset += size;
	return (ptr);
}

char	*arena_strdup(t_arena *arena, const char *str)
{
	char	*new_str;
	size_t	len;

	if (str == NULL)
		return (NULL);
	len = ft_strlen(str) + 1;
	new_str = (char *)alloc_arena(arena, len);
	if (new_str)
		ft_memcpy(new_str, str, len);
	return (new_str);
}

void	free_arena(t_arena *arena)
{
	if (arena && arena->buffer)
	{
		free(arena->buffer);
		arena->buffer = NULL;
		arena->size = 0;
		arena->offset = 0;
	}
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
