/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:24:03 by krepo             #+#    #+#             */
/*   Updated: 2025/07/17 12:02:53 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	ft_array_size(const char *s, char c);
static char		**ft_malloc_str(char **split, const char *s, char c, size_t i);
static char		**ft_strscpy(char **split, const char *s, char c);
static void		ft_free(char **split, size_t n);

char	**ft_split(char const *s, char c)
{
	size_t	size;
	char	**split;

	size = ft_array_size(s, c);
	split = ft_calloc((size + 1), sizeof(char *));
	if (split == NULL)
		return (NULL);
	ft_malloc_str(split, s, c, 0);
	ft_strscpy(split, s, c);
	return (split);
}

static size_t	ft_array_size(const char *s, char c)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] == '\0')
			break ;
		while (s[i] != c && s[i] != '\0')
			i++;
		size++;
	}
	return (size);
}

static	char	**ft_malloc_str(char **split, const char *s, char c, size_t i)
{
	size_t	j;
	size_t	size;

	j = 0;
	while (s[i] != '\0')
	{
		size = 0;
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		while (s[i] != c && s[i] != '\0')
		{
			size++;
			i++;
		}
		split[j] = malloc(size + 1);
		if (split[j] == NULL)
		{
			ft_free(split, j);
			return (NULL);
		}
		j++;
	}
	return (split);
}

static char	**ft_strscpy(char **split, const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		k = 0;
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		while (s[i] != c && s[i] != '\0')
		{
			split[j][k] = s[i];
			i++;
			k++;
		}
		split[j][k] = '\0';
		j++;
	}
	split[j] = 0;
	return (split);
}

static void	ft_free(char **split, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		free(split[i]);
		i++;
	}
	free(split);
}
