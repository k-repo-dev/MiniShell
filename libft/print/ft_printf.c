/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:07:57 by krepo             #+#    #+#             */
/*   Updated: 2025/07/17 14:04:41 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_check_format(const char specifier, va_list args);

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;
	int		i;

	va_start(args, format);
	i = 0;
	len = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			len += ft_check_format(format[i], args);
		}
		else
		{
			ft_putchar_fd(format[i], 1);
			len++;
		}
		i++;
	}
	va_end(args);
	return (len);
}

static int	ft_check_format(const char specifier, va_list args)
{
	if (specifier == 'c')
		return (ft_putchar_fd(va_arg(args, int), 1));
	else if (specifier == 's')
		return (ft_putstr_fd(va_arg(args, const char *), 1));
	else if (specifier == 'd' || specifier == 'i')
		return (ft_putnbr_fd(va_arg(args, int), 1));
	else if (specifier == 'u')
		return (ft_unbr_fd(va_arg(args, unsigned int), 1));
	else if (specifier == 'X' || specifier == 'x')
		return (ft_hexnbr_fd(va_arg(args, unsigned int), 1, specifier));
	else if (specifier == 'p')
		return (ft_putptr_fd(va_arg(args, void *), 1));
	else if (specifier == '%')
		return (ft_putchar_fd('%', 1));
	return (0);
}
