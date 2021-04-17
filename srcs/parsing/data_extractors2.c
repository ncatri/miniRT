/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_extractors2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 10:09:16 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/17 08:34:47 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

double	get_ratio(char *str)
{
	double	ratio;

	ratio = ft_atod(str);
	if (!str_isnumber(str) || ratio < 0 || ratio > 1)
		return (-1);
	else
		return (ratio);
}

double	get_fov(char *str)
{
	double	fov;

	fov = ft_atod(str);
	if (!str_isnumber(str) || fov < 0 || fov > 180)
		return (-1);
	else
		return (fov);
}

double	get_positive_val(char *str)
{
	double	val;

	val = ft_atod(str);
	if (!str_isnumber(str) || val < 0)
		return (-1);
	else
		return (val);
}
