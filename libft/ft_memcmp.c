/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 04:05:55 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/15 13:31:58 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_ptr;
	unsigned char	*s2_ptr;

	s1_ptr = (unsigned char *)s1;
	s2_ptr = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (--n && *s1_ptr == *s2_ptr)
	{
		s1_ptr++;
		s2_ptr++;
	}
	return ((int)(*s1_ptr - *s2_ptr));
}
