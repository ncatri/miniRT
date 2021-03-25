/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 08:21:06 by ncatrien          #+#    #+#             */
/*   Updated: 2021/03/25 08:53:02 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	ray_tracer(t_image image, t_scene scene)
{
	int i;
	int j;
	t_ray	ray;
	t_intersection	inter;

	i = -1;
	while (++i < scene.width)
	{
		j = -1;
		while (++j < scene.height)
		{
			inter = init_intersection();
			ray = primary_ray(i, j, scene);
			set_intersection(ray, scene, &inter);
			if (inter.obj != NULL)
			{
				inter.color = get_obj_color(inter.obj);
				pixel_put_image(image, i, j, inter.color);
			}
		}
	}
}

t_ray	primary_ray(int	x, int y, t_scene scene)
{
	t_ray	ray;
	t_camera *cam;

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

int	iter_cur_cam(t_scene *scene)
{
	if (scene->camera_list == NULL || scene->cur_cam == NULL)
		return (0);
	if (scene->cur_cam->next == NULL)
		scene->cur_cam = scene->camera_list;
	else
		scene->cur_cam = scene->cur_cam->next;
	return (1);
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

void	set_intersection(t_ray prim_ray, t_scene scene, t_intersection *inter)
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
			inter->color = get_obj_color(object); 
		}
		obj_cursor = obj_cursor->next;
	}
}

double	get_obj_intersect(t_object *obj, t_ray ray)
{
	if (obj->type == SPHERE)
		return (intersect_sp(obj->u.sp, ray));
	else
		return (INFINITY);
}

t_color	get_obj_color(t_object *obj)
{
	if (obj->type == SPHERE)
		return (obj->u.sp->color);
	else
		return (set_color(125,125,200));
}

