/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 08:21:06 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/20 09:13:02 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

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

t_ray	primary_ray(int	x, int y, t_scene scene)
{
	t_ray		ray;
	t_camera	*cam;

	cam = scene.cur_cam->content;
	x = x - scene.width / 2;
	y = scene.height / 2 - y;
	ray.direction.x = cam->position.x / 2 - x;
	ray.direction.y = y - cam->position.y / 2;
	ray.direction.z = scene.width / \
					  (2 * tan(cam->fov * M_PI / (2 * 180)));
	ray.direction = mult_vec_matrix(cam->c2w_matrix, ray.direction);
	ray.direction = normalized(ray.direction);
	ray.origin = cam->position;
	return (ray);
}

/* new version

t_ray	primary_ray(int i, int j, t_scene scene)
{
	t_ray		ray;
	t_camera	*cam;
	double		px;
	double		py;
	double		h;
	double		w;
	t_coordinates	pix_coord;

	t_coordinates	u;
	t_coordinates	v;
	t_coordinates	vxu;

	cam = scene.cur_cam->content;
	w = scene.ratio * tan(cam->fov * M_PI / (2 * 180));
	h = tan(cam->fov * M_PI / (2 * 180));
	px = h - (j + 0.5) * 2 * h / scene.height;
	py = (i + 0.5) * 2 * w / scene.width - w;

	u = set_coordinates(0, 1, 0);
	if (is_equal(cam->orientation, u) || |
			is_equal(cam->orientation, scalar_mult(-1,u)))
		u = set_coordinates(0, 0, 1);
	v = cam->orientation;
	vxu = cross_product(v, u);
	pix_coord = add(scalar_mult(px, u), scalar_mult(py, vxu));
	pix_coord = add(add(cam->position, v), pix_coord);
	ray.direction = substract(pix_coord, cam->position);
	ray.direction = normalized(ray.direction);
	ray.origin = cam->position;
	return (ray);
}
*/

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
