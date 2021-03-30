/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 11:41:39 by ncatrien          #+#    #+#             */
/*   Updated: 2021/03/30 11:43:18 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	compute_shading(t_scene scene, t_ray prim_ray, t_intersection *inter)
{
	(void)prim_ray;
	t_intersection	inter_light;
	t_ray			light_ray;

	inter->color =  ambient_light(inter->color, scene.ambient);
	while (iter_cur_light(&scene))
	{
		light_ray = cast_light_ray(scene, inter);
		if (get_light(scene, inter, &inter_light))
		{
			inter->color = set_color(255,255,255);
		//	inter->color = add_diffuse(inter->color, inter, inter_light); 
		}
	}
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

t_bool	get_light(t_scene scene, t_intersection *inter, t_intersection *inter_light)
{
	t_ray	light_ray;
	t_light	*light;

//	light = scene.light_list->content;
	light = scene.cur_light->content;

	light_ray.origin = inter->p_hit;
	light_ray.direction = substract(light->position, inter->p_hit);
	light_ray.direction = normalized(light_ray.direction);
	
	*inter_light = init_intersection();
	if (found_intersection(light_ray, scene, inter_light))
	{
		if (inter_light->min_dist < sqrt(get_norm2(substract(light->position, inter->p_hit))))
			return (FALSE);
	}
	return (TRUE);
}
/*
t_color	add_diffuse(t_color color, t_intersection *inter, t_intersection inter_light){
	t_color diffuse;
	t_coordinates	l;
	t_coordinates	n;

	l = inter_light.
	diffuse = 

}
*/
t_bool	iter_cur_light(t_scene *scene)
{
	if (scene && scene->light_list)
	{
		if (scene->cur_light == NULL)
			scene->cur_light = scene->light_list;
		else if (scene->cur_light->next != NULL)
			scene->cur_light = scene->cur_light->next;
		else
			return (FALSE);
		return (TRUE);
	}
	return (FALSE);
}
