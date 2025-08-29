/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 07:54:08 by krepo             #+#    #+#             */
/*   Updated: 2025/07/17 11:55:48 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*tmp;
	size_t	i;

	i = nmemb * size;
	if (i == 0)
		return (malloc(0));
	if (i / nmemb != size)
		return (NULL);
	tmp = malloc(i);
	if (tmp == NULL)
		return (NULL);
	ft_memset(tmp, '\0', i);
	return (tmp);
}
