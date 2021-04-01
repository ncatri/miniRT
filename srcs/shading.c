/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 11:41:39 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/01 13:25:41 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

# define SHININESS (10)

void	compute_shading(t_scene scene, t_ray prim_ray, t_intersection *inter)
{
	(void)prim_ray;
	t_intersection	inter_light;
	t_ray			light_ray;
	t_light			*light;
	t_color			ambient;
	t_color			diffuse;
	t_color			specular;

	ambient = mult_color(inter->color, scene.ambient.intensity);
	inter->color = ambient;
	while (iter_cur_light(&scene))
	{
		light = scene.cur_light->content;
		light_ray = cast_light_ray(scene, inter);
		if (get_light(scene, inter, &inter_light, light_ray))
		{
			diffuse = add_diffuse(inter, light_ray, light); 
			specular = add_specular(inter, light_ray, light, prim_ray);
			inter->color = add_colors(diffuse, inter->color);
			inter->color = add_colors(specular, inter->color);
		}
	}
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
	diffuse = mult_color(k, scalar_mult(incidence, light->intensity));
	return (diffuse);
}

t_color add_specular(t_intersection *inter, t_ray light_ray, t_light *light, \
		t_ray prim_ray)
{
	t_coordinates reflect;
	t_coordinates v;
	t_coordinates l;
	double coef;
	t_color		specular;

	v = scalar_mult(-1, prim_ray.direction);
	l = scalar_mult(-1, light_ray.direction);
	reflect = substract(scalar_mult(2 * dot(inter->norm_hit, l), inter->norm_hit), l);
	coef = pow(dot(reflect, v), SHININESS);
	specular = mult_color(inter->color, scalar_mult(coef, light->intensity));
	return (specular);	
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

	res.r = fmin(color1.r + color2.r, 255);
	res.g = fmin(color1.g + color2.g, 255);
	res.b = fmin(color1.b + color2.b, 255);
	res = set_color(res.r, res.g, res.b);
	return (res);
}
