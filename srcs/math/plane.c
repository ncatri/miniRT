/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 07:39:49 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/06 11:12:03 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

double	intersect_pl(t_plane *pl, t_ray ray)
{
	double	t;
	double	denom;
	t_coordinates	p0l0;

	denom = dot(ray.direction, pl->orientation);
	if (fabs(denom) < 0.001) 
		return (INFINITY);
	p0l0 = substract(pl->position, ray.origin);
	t = dot(p0l0, pl->orientation) / denom;
	if (t < 0)
		return (INFINITY);
	return (t);
}
