/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 08:21:06 by ncatrien          #+#    #+#             */
/*   Updated: 2021/03/22 13:42:17 by ncatrien         ###   ########lyon.fr   */
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
	inter = init_intersection();
	while (i < scene.width)
	{
		j = 0;
		while (j < scene.height)
		{
			ray = primary_ray(i, j, scene);
			ray.direction = normalized(ray.direction);
			if (intersect_sp(sp, ray))
				pixel_put_image(image, i, j, sp->color); 
			else
			{
				t_color background = set_color(255,255,255);
				pixel_put_image(image, i, j, background); 
			}
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

//	ray direction in the camera base
	ray.direction.x = cam->position.x / 2 - x;
	ray.direction.y = y - cam->position.y / 2;
	ray.direction.z = scene.width / \
					  (2 * tan(cam->fov * M_PI / (2 * 180)));

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

	inter.t = INFINITY;
	inter.obj = NULL;
	return (inter);
}
