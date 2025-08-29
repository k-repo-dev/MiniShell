/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 09:34:41 by krepo             #+#    #+#             */
/*   Updated: 2025/07/17 12:04:50 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	size_t	j;
	size_t	i;
	size_t	len;
	size_t	k;

	if (!s1)
		return (NULL);
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	j = ft_strlen(s1);
	while (j > i && ft_strchr(set, s1[j - 1]))
		j--;
	len = j - i;
	s2 = (char *)malloc(len + 1);
	if (!s2)
		return (NULL);
	k = 0;
	while (i < j)
		s2[k++] = s1[i++];
	s2[k] = '\0';
	return (s2);
}
