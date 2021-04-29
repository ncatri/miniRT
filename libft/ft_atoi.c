/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 03:51:44 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/15 13:21:00 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	my_isspace(int c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}

static	int	is_long_overflow(const char *num)
{
	int	num_len;

	num_len = 0;
	while (*num && ft_isdigit(*num))
	{
		num_len++;
		num++;
	}
	if (num_len >= 19)
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (my_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	if (is_long_overflow(nptr) && sign == -1)
		return (0);
	if (is_long_overflow(nptr) && sign == 1)
		return (-1);
	while (ft_isdigit(*nptr))
	{
		result = result * 10 + *nptr - '0';
		nptr++;
	}
	return (sign * result);
}
