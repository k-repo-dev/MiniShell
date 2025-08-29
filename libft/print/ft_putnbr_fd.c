/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 08:37:47 by krepo             #+#    #+#             */
/*   Updated: 2025/07/17 12:00:36 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	int	len;

	len = 0;
	if (n == (-2147483648))
	{
		write(fd, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		len += ft_putchar_fd('-', fd);
		len += ft_putnbr_fd(-n, fd);
	}
	else if (n > 9)
	{
		len += ft_putnbr_fd(n / 10, fd);
		len += ft_putnbr_fd(n % 10, fd);
	}
	else
		len += ft_putchar_fd(n + '0', fd);
	return (len);
}
