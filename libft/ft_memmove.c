/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 04:08:08 by ncatrien          #+#    #+#             */
/*   Updated: 2020/11/24 06:16:22 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char *dst_ptr;
	char *src_ptr;

	if (dst == 0 && src == 0)
		return (NULL);
	dst_ptr = (char*)dst;
	src_ptr = (char*)src;
	if (src > dst)
		ft_memcpy(dst, src, len);
	else
	{
		dst_ptr += len - 1;
		src_ptr += len - 1;
		while (len--)
		{
			*dst_ptr = *src_ptr;
			src_ptr--;
			dst_ptr--;
		}
	}
	return (dst);
}
