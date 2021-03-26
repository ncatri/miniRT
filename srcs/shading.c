/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 11:41:39 by ncatrien          #+#    #+#             */
/*   Updated: 2021/03/26 16:42:53 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	compute_shading(t_scene scene, t_ray prim_ray, t_intersection *inter)
{
	(void)prim_ray;

	inter->color =  ambient_light(inter->color, scene.ambient);
/*
	if (!is_inshadow)
	{
		for every light
			diffuse_light;
			specular_light;
	}
*/
}

t_color ambient_light(t_color obj_color, t_light ambient)
{
	t_color res;

	res = mult_color(obj_color, ambient.intensity);
	return (res);
}

t_color	mult_color(t_color color, t_coordinates mult)
{
	t_color	res;
	int		red;
	int		green;
	int		blue;

	red = fmin(color.r * mult.x, 255);
	green = fmin(color.g * mult.y, 255);
	blue = fmin(color.b * mult.z, 255);
	res = set_color(red, green, blue);
	return (res);
}
