/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 03:51:01 by ncatrien          #+#    #+#             */
/*   Updated: 2020/11/26 02:17:26 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*ptr;

	if (!alst || !new)
		return ;
	if (*alst == 0)
	{
		*alst = new;
		return ;
	}
	if (new == 0)
		return ;
	ptr = *alst;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}
