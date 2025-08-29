/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:46:34 by krepo             #+#    #+#             */
/*   Updated: 2025/07/17 11:56:31 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*tdst;
	char	*tsrc;
	size_t	i;

	tdst = (char *) dst;
	tsrc = (char *) src;
	i = 0;
	if (tdst < tsrc)
	{
		while (i < n)
		{
			tdst[i] = tsrc[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i > 0)
		{
			i--;
			tdst[i] = tsrc[i];
		}
	}
	return (dst);
}
