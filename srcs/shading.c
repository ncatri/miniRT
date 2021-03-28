/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 11:41:39 by ncatrien          #+#    #+#             */
/*   Updated: 2021/03/28 13:46:30 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	compute_shading(t_scene scene, t_ray prim_ray, t_intersection *inter)
{

	inter->color =  ambient_light(inter->color, scene.ambient);
	if (!is_inshadow(scene, prim_ray, inter))
	{
		inter->color = set_color(255,255,255);
	}

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
	t_color result;

	result = mult_color(obj_color, ambient.intensity);
	return (result);
}

t_color	mult_color(t_color color, t_coordinates mult)
{
	t_color	result;
	int		red;
	int		green;
	int		blue;

	red = fmin(color.r * mult.x, 255);
	green = fmin(color.g * mult.y, 255);
	blue = fmin(color.b * mult.z, 255);
	result = set_color(red, green, blue);
	return (result);
}

t_bool	is_inshadow(t_scene scene, t_ray prim_ray, t_intersection *inter)
{
	(void)prim_ray;
	t_intersection	inter_light;
	t_ray	light_ray;
	t_light	*light;

	light = scene.light_list->content;

	light_ray.origin = inter->p_hit;
	light_ray.direction = substract(light->position, inter->p_hit);
	light_ray.direction = normalized(light_ray.direction);
	
	inter_light = init_intersection();
	if (found_intersection(light_ray, scene, &inter_light))
	{
		if (inter_light.min_dist < sqrt(get_norm2(substract(light->position, inter->p_hit))))
			return (FALSE);
	}
	return (TRUE);
}
