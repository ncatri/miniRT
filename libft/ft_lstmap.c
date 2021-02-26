/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 06:00:11 by ncatrien          #+#    #+#             */
/*   Updated: 2020/11/25 06:41:20 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_elt;
	t_list	*cursor;

	if (!lst)
		return (0);
	new_lst = 0;
	cursor = lst;
	while (cursor)
	{
		new_elt = ft_lstnew((*f)(cursor->content));
		ft_lstadd_back(&new_lst, new_elt);
		if (!new_elt)
		{
			ft_lstclear(&new_lst, del);
			return (0);
		}
		cursor = cursor->next;
	}
	return (new_lst);
}
