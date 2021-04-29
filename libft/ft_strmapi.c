/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 02:09:10 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/15 13:40:20 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ptr;
	size_t			len;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (ptr)
	{
		i = -1;
		while (++i < len)
			ptr[i] = (*f)(i, s[i]);
		ptr[i] = '\0';
	}
	return (ptr);
}
