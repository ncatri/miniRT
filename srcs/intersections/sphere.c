/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:35:26 by ncatrien          #+#    #+#             */
/*   Updated: 2021/03/22 14:32:26 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

double	intersect_sp(t_sphere *sp, t_ray ray)
{
	t_polynome2deg	poly;

	poly.a = 1;
	poly.b = 2 * dot(ray.direction, substract(ray.origin, sp->centre));
	poly.c = get_norm2(substract(ray.origin, sp->centre)) - \
		(sp->diameter / 2) * (sp->diameter / 2);
	poly.delta = poly.b * poly.b - 4 * poly.a * poly.c;
	if (poly.delta < 0)
		return (INFINITY);
	poly.sol1 = (-poly.b + sqrt(poly.delta)) / (2 * poly.a);
	poly.sol2 = (-poly.b - sqrt(poly.delta)) / (2 * poly.a);
	if (poly.sol1 < 0)
		return (INFINITY);
	if (poly.sol2 > 0)
		return (poly.sol2);
	else
		return (poly.sol1);
}
