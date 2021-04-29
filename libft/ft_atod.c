/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 09:34:16 by ncatrien          #+#    #+#             */
/*   Updated: 2021/03/02 10:16:35 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	my_isspace(int c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}

static double	add_decimal(const char *nptr)
{
	double	result;
	double	decimal;

	result = 0;
	decimal = 10;
	nptr++;
	while (ft_isdigit(*nptr))
	{
		result += (*nptr - '0') / (double)decimal;
		decimal *= 10;
		nptr++;
	}
	return (result);
}

double	ft_atod(const char *nptr)
{
	double	result;
	int		sign;

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
	while (ft_isdigit(*nptr))
	{
		result = result * 10 + *nptr - '0';
		nptr++;
	}
	if (*nptr == '.')
		result += add_decimal(nptr);
	return (sign * result);
}
