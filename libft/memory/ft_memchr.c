/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:46:36 by krepo             #+#    #+#             */
/*   Updated: 2025/07/17 11:55:59 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ts;
	unsigned char	tc;

	tc = (unsigned char) c;
	ts = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (ts[i] == tc)
			return ((void *) &ts[i]);
		i++;
	}
	return (0);
}
