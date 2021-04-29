/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 04:05:36 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/15 13:29:33 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dst_ptr;
	size_t	i;

	if (dst == 0 && src == 0)
		return (NULL);
	dst_ptr = (char *)dst;
	i = -1;
	while (++i < n)
	{
		*dst_ptr = *((char *)src + i);
		dst_ptr++;
	}
	return (dst);
}
