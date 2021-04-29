/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 06:09:11 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/15 13:44:32 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	is_inset(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	char	*end;
	char	*result;
	long	i;

	if (!s1 || !set)
		return (NULL);
	start = (char *)s1;
	while (is_inset(*start, set))
		start++;
	end = (char *)s1 + ft_strlen(s1);
	while (is_inset(*(end - 1), set) && end >= start)
		end--;
	result = (char *)malloc(sizeof(char) * (end - start + 1));
	if (result)
	{
		i = -1;
		while (++i < (end - start))
			result[i] = start[i];
		result[i] = '\0';
	}
	return (result);
}
