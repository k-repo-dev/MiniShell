/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 09:14:07 by krepo             #+#    #+#             */
/*   Updated: 2025/07/17 11:55:25 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*tmp_lst;
	size_t	i;

	i = 0;
	tmp_lst = lst;
	while (tmp_lst)
	{
		tmp_lst = tmp_lst->next;
		i++;
	}
	return (i);
}
