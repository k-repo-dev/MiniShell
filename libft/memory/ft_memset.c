/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:47:02 by krepo             #+#    #+#             */
/*   Updated: 2025/07/17 11:56:41 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*cc;

	cc = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		cc[i] = (unsigned char) c;
		i++;
	}
	return (s);
}
