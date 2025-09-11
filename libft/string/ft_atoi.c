/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:28:53 by krepo             #+#    #+#             */
/*   Updated: 2025/07/17 12:02:24 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_atoi(const char *nptr)
{
	long long	fvalue;
	int			nvalue;
	size_t		i;

	fvalue = 0;
	nvalue = 0;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			nvalue++;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		fvalue = fvalue * 10 + (nptr[i] - '0');
		i++;
	}
	if (nvalue == 1)
		fvalue = fvalue * (-1);
	return ((int) fvalue);
}
