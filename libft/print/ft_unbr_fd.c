/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unbr_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 08:55:57 by krepo             #+#    #+#             */
/*   Updated: 2025/07/17 12:02:08 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_unbr_fd(unsigned int n, int fd)
{
	unsigned int	nb;
	unsigned int	len;

	len = 0;
	nb = n;
	if (n > 9)
	{
		len += ft_unbr_fd(nb / 10, fd);
		len += ft_unbr_fd(nb % 10, fd);
	}
	else
	{
		nb += '0';
		len += write(fd, &nb, 1);
	}
	return (len);
}
