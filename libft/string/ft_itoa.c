/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:40:05 by krepo             #+#    #+#             */
/*   Updated: 2025/07/17 12:02:41 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	ft_counter(long long temp_n);

char	*ft_itoa(int n)
{
	size_t		len;
	long long	temp_n;
	char		*result;

	temp_n = (long long)n;
	len = ft_counter(temp_n);
	result = malloc(len + 1);
	if (result == NULL)
		return (NULL);
	if (temp_n == 0)
		result[0] = '0';
	if (temp_n < 0)
	{
		temp_n = -temp_n;
		result[0] = '-';
	}
	result[len] = '\0';
	while (len > 0 && temp_n != 0)
	{
		result[len - 1] = (temp_n % 10) + '0';
		temp_n = temp_n / 10;
		len--;
	}
	return (result);
}

static size_t	ft_counter(long long temp_n)
{
	size_t	len;

	len = 0;
	if (temp_n < 0)
	{
		temp_n = -temp_n;
		len++;
	}
	while (temp_n > 9)
	{
		temp_n = temp_n / 10;
		len++;
	}
	len++;
	return (len);
}
