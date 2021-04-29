/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 04:36:15 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/15 13:46:09 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	int		flag;

	flag = 1;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		flag = 0;
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (ptr)
	{
		i = 0;
		while (i < len && flag && s[start + i])
		{
			ptr[i] = s[start + i];
			i++;
		}
		ptr[i] = '\0';
	}
	return (ptr);
}
