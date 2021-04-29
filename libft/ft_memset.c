/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 04:06:36 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/15 13:32:46 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *b, int c, size_t len)
{
	char			*ptr;
	unsigned char	set_value;

	ptr = (char *)b;
	set_value = (unsigned char)c;
	while (len--)
	{
		*ptr = set_value;
		ptr++;
	}
	return (b);
}
