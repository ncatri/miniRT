/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 17:47:36 by ncatrien          #+#    #+#             */
/*   Updated: 2020/12/07 15:55:21 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dst_ptr;
	size_t	i;

	if (dst == 0 && src == 0)
		return (NULL);
	dst_ptr = (char*)dst;
	i = -1;
	while (++i < n)
	{
		*dst_ptr = *((char*)src + i);
		dst_ptr++;
	}
	return (dst);
}
