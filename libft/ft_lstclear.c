/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 04:19:57 by ncatrien          #+#    #+#             */
/*   Updated: 2020/11/26 02:21:03 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*cursor;
	t_list	*next;

	if (!lst || *lst == 0)
		return ;
	cursor = *lst;
	while (cursor)
	{
		next = cursor->next;
		(*del)(cursor->content);
		free(cursor);
		cursor = next;
	}
	*lst = 0;
}
