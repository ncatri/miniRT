/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:33:14 by ncatrien          #+#    #+#             */
/*   Updated: 2021/02/25 10:46:59 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_coordinates	add(const t_coordinates a, const t_coordinates b)
{
	t_coordinates	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_coordinates	substract(const t_coordinates a, const t_coordinates b)
{
	t_coordinates	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

double	dot(t_coordinates a, t_coordinates b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

double	get_norm2(const t_coordinates a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}

t_coordinates	normalized(t_coordinates v)
{
	t_coordinates	result;
	double			norm;

	norm = sqrt(get_norm2(v));
	result.x = v.x / norm;
	result.y = v.y / norm;
	result.z = v.z / norm;
	return (result);
}	
