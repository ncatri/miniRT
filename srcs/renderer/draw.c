/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 08:21:06 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/28 10:48:33 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ray_tracer(t_scene scene)
{
	int				i;
	int				j;
	t_ray			ray;
	t_intersection	inter;

	i = -1;
	while (++i < scene.width)
	{
		j = -1;
		while (++j < scene.height)
		{
			inter = init_intersection();
			ray = primary_ray(i, j, scene);
			if (found_intersection(ray, scene, &inter))
			{
				set_intersection(ray, scene, &inter);
				compute_shading(scene, ray, &inter);
				if (scene.save_bmp)
					color_put_buffer(scene, i, j, inter.color);
				else
					pixel_put_image(scene.image, i, j, inter.color);
			}
		}
	}
	return (1);
}

t_ray	primary_ray(int i, int j, t_scene scene)
{
	t_ray		ray;
	t_camera	*cam;
	t_primray	p;

	cam = scene.cur_cam->content;
	p.w = scene.ratio * tan(cam->fov * M_PI / (2 * 180));
	p.h = tan(cam->fov * M_PI / (2 * 180));
	p.px = p.h - (j + 0.5) * 2 * p.h / scene.height;
	p.py = (i + 0.5) * 2 * p.w / scene.width - p.w;
	p.u = set_coordinates(0, 1, 0);
	if (is_equal(cam->orientation, p.u) || \
			is_equal(cam->orientation, scalar_mult(-1, p.u)))
		p.u = set_coordinates(0, 0, 1);
	p.v = cam->orientation;
	p.vxu = cross_product(p.v, p.u);
	p.pix_coord = add(scalar_mult(p.px, p.u), scalar_mult(p.py, p.vxu));
	p.pix_coord = add(add(cam->position, p.v), p.pix_coord);
	ray.direction = substract(p.pix_coord, cam->position);
	ray.direction = normalized(ray.direction);
	ray.origin = cam->position;
	return (ray);
}

t_intersection	init_intersection(void)
{
	t_intersection	inter;

	inter.min_dist = INFINITY;
	inter.p_hit = set_coordinates(0, 0, 0);
	inter.norm_hit = set_coordinates(0, 0, 0);
	inter.obj = NULL;
	return (inter);
}

t_bool	found_intersection(t_ray prim_ray, t_scene scene, t_intersection *inter)
{
	t_list		*obj_cursor;
	t_object	*object;
	double		t;

	obj_cursor = scene.objects_list;
	while (obj_cursor != NULL)
	{
		object = obj_cursor->content;
		t = get_obj_intersect(object, prim_ray);
		if (t < inter->min_dist)
		{
			inter->min_dist = t;
			inter->obj = object;
		}
		obj_cursor = obj_cursor->next;
	}
	return (inter->min_dist != INFINITY);
}

void	set_intersection(t_ray prim_ray, t_scene scene, t_intersection *inter)
{
	(void)scene;
	inter->color = get_obj_color(inter->obj);
	inter->p_hit = add(prim_ray.origin, \
			scalar_mult(inter->min_dist, prim_ray.direction));
	inter->norm_hit = get_normal(inter, prim_ray);
	inter->p_hit = add(scalar_mult(ACNEA, inter->norm_hit), inter->p_hit);
}
