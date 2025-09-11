/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 09:08:39 by krepo             #+#    #+#             */
/*   Updated: 2025/07/17 14:04:12 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	convert_hex(uintptr_t n, int fd);
static void	puthex(uintptr_t n, int fd);

int	ft_putptr_fd(void *n, int fd)
{
	if (n == 0)
		return (ft_putstr_fd("(nil)", fd));
	ft_putstr_fd("0x", fd);
	return (convert_hex((uintptr_t)n, fd) + 2);
}

static int	convert_hex(uintptr_t n, int fd)
{
	int	res;

	if (n == 0)
		return (0);
	res = 1 + convert_hex(n / 16, fd);
	puthex(n % 16, fd);
	return (res);
}

static void	puthex(uintptr_t n, int fd)
{
	if (n <= 9)
		ft_putchar_fd(n + '0', fd);
	else if (n >= 10 && n <= 15)
		ft_putchar_fd(n + 87, fd);
}
