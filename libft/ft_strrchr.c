/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 04:13:55 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/15 13:42:55 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	size_t	len;

	str = (char *)s;
	len = ft_strlen(s);
	str += len;
	while (*str != (unsigned char)c && len--)
		str--;
	if (*str == (unsigned char)c)
		return (str);
	else
		return (NULL);
}
