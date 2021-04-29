/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 04:12:59 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/15 13:36:06 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	i;

	ptr = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (ptr)
	{
		i = -1;
		while (s[++i])
			ptr[i] = s[i];
		ptr[i] = '\0';
	}
	return (ptr);
}
