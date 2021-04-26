/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 11:41:39 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/26 14:41:50 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	compute_shading(t_scene scene, t_ray prim_ray, t_intersection *inter)
{
	t_ray			light_ray;
	t_light			*light;
	t_color			diffuse;
	t_color			specular;
	t_color			shading;

	shading = set_color(0, 0, 0);
	while (iterate_current_light(&scene))
	{
		light = scene.cur_light->content;
		light_ray = cast_light_ray(light, inter);
		if (get_light(scene, inter, light_ray))
		{
			diffuse = add_diffuse(inter, light_ray, light);
			specular = add_specular(inter, light_ray, light, prim_ray);
			shading = add_colors(shading, diffuse);
			shading = add_colors(shading, specular);
		}
	}
	inter->color = add_colors(shading, \
			mult_color(inter->color, scene.ambient.intensity));
}

t_bool	get_light(t_scene scene, t_intersection *inter, t_ray light_ray)
{
	t_light			*light;
	t_intersection	inter_light;
	double			distance_to_light;

	light = scene.cur_light->content;
	inter_light = init_intersection();
	if (found_intersection(light_ray, scene, &inter_light))
	{
		distance_to_light = sqrt(get_norm2(
					substract(light->position, inter->p_hit)));
		if (inter_light.min_dist < distance_to_light)
			return (FALSE);
	}
	return (TRUE);
}

t_ray	cast_light_ray(t_light *light, t_intersection *inter)
{
	t_ray	ray;

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
	diffuse = mult_color(k, scalar_mult(incidence, light->intensity));
	return (diffuse);
}

t_color	add_specular(t_intersection *inter, t_ray light_ray, t_light *light, \
		t_ray prim_ray)
{
	t_coordinates	reflect;
	t_coordinates	v;
	t_coordinates	l;
	double			coef;
	t_color			specular;

	v = scalar_mult(-1, prim_ray.direction);
	l = light_ray.direction;
	reflect = substract(
			scalar_mult(2 * dot(inter->norm_hit, l), inter->norm_hit), l);
	coef = fmax(0, dot(reflect, v));
	coef = pow(coef, SHININESS);
	specular = mult_color(inter->color, scalar_mult(coef, light->intensity));
	return (specular);
}
