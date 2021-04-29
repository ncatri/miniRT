/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 04:15:29 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/15 13:41:32 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!needle[0])
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		while (needle[j] && haystack[i + j] && (haystack[i + j] == needle[j]) \
				&& (i + j < len))
			j++;
		if (needle[j] == '\0')
			return ((char *)haystack + i);
		j = 0;
		i++;
	}
	return (NULL);
}
