/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:41:08 by krepo             #+#    #+#             */
/*   Updated: 2025/07/17 12:01:58 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putstr_fd(const char *s, int fd)
{
	int	len;

	len = 0;
	if (!s)
		return (write(fd, "(null)", 6));
	while (*s)
	{
		write(fd, s, 1);
		len++;
		s++;
	}
	return (len);
}
