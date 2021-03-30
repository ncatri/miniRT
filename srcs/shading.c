/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 11:41:39 by ncatrien          #+#    #+#             */
/*   Updated: 2021/03/30 15:20:45 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	compute_shading(t_scene scene, t_ray prim_ray, t_intersection *inter)
{
	(void)prim_ray;
	t_intersection	inter_light;
	t_ray			light_ray;
	t_light			*light;

	inter->color =  ambient_light(inter->color, scene.ambient);
	while (iter_cur_light(&scene))
	{
		light = scene.cur_light->content;
		light_ray = cast_light_ray(scene, inter);
		if (get_light(scene, inter, &inter_light, light_ray))
		{
			inter->color = add_diffuse(inter, light_ray, light); 
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

t_bool	get_light(t_scene scene, t_intersection *inter, \
		t_intersection *inter_light, t_ray light_ray)
{
	t_light	*light;

	light = scene.cur_light->content;
	*inter_light = init_intersection();
	if (found_intersection(light_ray, scene, inter_light))
	{
		if (inter_light->min_dist < sqrt(get_norm2(substract(light->position, inter->p_hit))))
			return (FALSE);
	}
	return (TRUE);
}

t_ray	cast_light_ray(t_scene scene, t_intersection *inter)
{
	t_ray	ray;
	t_light	*light;

	light = scene.cur_light->content;
	ray.origin = inter->p_hit;
	ray.direction = substract(light->position, inter->p_hit);
	ray.direction = normalized(ray.direction);
	return (ray);
}

t_color	add_diffuse(t_intersection *inter, t_ray light_ray, t_light *light)
{
	t_color		diffuse;
	double		incidence;
	t_color		k;

	k = inter->color;
	incidence = fmax(0, dot(inter->norm_hit, light_ray.direction));
	diffuse.t = 0;
	diffuse.r = fmin(k.r + light->color.r * light->ratio * incidence, 255);
	diffuse.g = fmin(k.g + light->color.g * light->ratio * incidence, 255);
	diffuse.b = fmin(k.b + light->color.b * light->ratio * incidence, 255);
	diffuse.value = create_trgb(diffuse);
	return (diffuse);
}

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

t_color	add_colors(t_color color1, t_color color2)
{
	t_color	res;

	res.r = (color1.r + color2.r) / 2;
	res.g = (color1.g + color2.g) / 2;
	res.b = (color1.b + color2.b) / 2;
	return (res);
}
