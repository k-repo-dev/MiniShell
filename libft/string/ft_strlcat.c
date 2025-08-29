/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:24:19 by krepo             #+#    #+#             */
/*   Updated: 2025/07/17 12:03:41 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstl;
	size_t	srcl;
	size_t	i;

	dstl = ft_strlen(dst);
	srcl = ft_strlen(src);
	i = 0;
	if (size == 0)
		return (srcl);
	if (dstl >= size)
		return (size + srcl);
	while (src[i] != '\0' && dstl + i < size - 1)
	{
		dst[i + dstl] = src[i];
		i++;
	}
	dst[dstl + i] = '\0';
	return (dstl + srcl);
}
