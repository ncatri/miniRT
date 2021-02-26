/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 05:46:22 by ncatrien          #+#    #+#             */
/*   Updated: 2020/11/25 05:57:51 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*cursor;

	if (!lst)
		return ;
	cursor = lst;
	while (cursor)
	{
		(*f)(cursor->content);
		cursor = cursor->next;
	}
}
