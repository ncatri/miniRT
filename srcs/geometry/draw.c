/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 08:21:06 by ncatrien          #+#    #+#             */
/*   Updated: 2021/03/23 12:49:58 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	ray_tracer(t_image image, t_scene scene)
{
	int i;
	int j;
	t_ray	ray;
	t_intersection	inter;

	t_sphere *sp;
	t_object *obj;
	obj = scene.objects_list->content;
	sp = obj->u.sp;

	i = 0;
	while (i < scene.width)
	{
		j = 0;
		while (j < scene.height)
		{
			inter = init_intersection();
			ray = primary_ray(i, j, scene);
			get_intersection(ray, scene, &inter);
/*
			if (intersect_sp(sp, ray))
				pixel_put_image(image, i, j, sp->color); 
			else
			{
				t_color background = set_color(255,255,255);
				pixel_put_image(image, i, j, background); 
			}
*/
			j++;
		}
		i++;
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
/*
t_bool	intersect(t_scene *scene, t_ray prim_ray, t_intersection *inter)
{
	t_object	*obj;

	obj = scene->cur_object->content;
	if (obj->type == SPHERE)
		return (intersect_sp((obj.u.sp), prim_ray));
	else
		return (FALSE);
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

void	get_intersection(t_ray prim_ray, t_scene scene, t_intersection *inter)
{
	t_object *object;
	double	t;

	object = scene.objects_list;
	while (object != NULL)
	{
		t = intersect(object, prim_ray);
		if (t < inter->min_dist)
		{
			inter->min_dist = t;
			inter->obj = object;
		}
		object = object->next;
	}
}

double	intersect(t_object *obj, t_ray ray)
{
	if (obj->type == SPHERE)
		return (intersect_sp(obj->u.sp, ray));
	else
		return (INFINITY);
}
