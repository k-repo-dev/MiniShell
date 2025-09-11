/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 08:58:54 by krepo             #+#    #+#             */
/*   Updated: 2025/07/17 11:56:53 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	convert_hex(unsigned int n, int fd, char specifier);
static void	puthex(unsigned int n, int fd, char specifier);

int	ft_hexnbr_fd(unsigned int n, int fd, char specifier)
{
	if (n == 0)
		return (ft_putchar_fd(n + '0', fd));
	return (convert_hex(n, fd, specifier));
}

static int	convert_hex(unsigned int n, int fd, char specifier)
{
	int	res;

	if (n == 0)
		return (0);
	res = 1 + convert_hex(n / 16, fd, specifier);
	puthex(n % 16, fd, specifier);
	return (res);
}

static void	puthex(unsigned int n, int fd, char specifier)
{
	if (n <= 9)
		ft_putchar_fd(n + '0', fd);
	else if (n >= 10 && n <= 15)
	{
		if (specifier == 'X')
			ft_putchar_fd((n + 55), fd);
		if (specifier == 'x')
			ft_putchar_fd((n + 87), fd);
	}
}
