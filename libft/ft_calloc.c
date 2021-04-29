/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 03:56:29 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/15 13:21:44 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	memory;
	void	*ptr;

	memory = nmemb * size;
	ptr = malloc(memory);
	if (!ptr)
		return (NULL);
	while (memory--)
		*((char *)ptr + memory) = 0;
	return ((void *)ptr);
}
