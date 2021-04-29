/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 04:11:49 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/15 13:37:03 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	count;
	size_t	src_len;
	size_t	dst_len;

	count = 0;
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (dst_len >= size)
		return (src_len + size);
	while (src[count] && (size - 1 > count + dst_len))
	{
		dst[dst_len + count] = src[count];
		count++;
	}
	dst[count + dst_len] = '\0';
	return (dst_len + src_len);
}
