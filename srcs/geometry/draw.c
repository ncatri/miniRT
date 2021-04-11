/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 08:21:06 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/11 15:26:15 by ncatrien         ###   ########lyon.fr   */
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
			if (found_intersection(ray, scene, &inter))
			{
				set_intersection(ray, scene, &inter);
		//		compute_shading(scene, ray, &inter);
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

double	get_obj_intersect(t_object *obj, t_ray ray)
{
	if (obj->type == SPHERE)
		return (intersect_sp(obj->u.sp, ray));
	else if (obj->type == PLANE)
		return (intersect_pl(obj->u.pl, ray));
	else if (obj->type == SQUARE)
		return (intersect_sq(obj->u.sq, ray));
	else if(obj->type == TRIANGLE)
		return (intersect_tr(obj->u.tr, ray));
	else if (obj->type == CYLINDER)
		return (intersect_cy(obj->u.cy, ray));
	else
		return (INFINITY);
}

t_color	get_obj_color(t_object *obj)
{
	if (obj->type == SPHERE)
		return (obj->u.sp->color);
	else if (obj->type == PLANE)
		return (obj->u.pl->color);
	else if (obj->type == SQUARE)
		return (obj->u.sq->color);
	else if (obj->type == TRIANGLE)
		return (obj->u.tr->color);
	else if (obj->type == CYLINDER)
		return (obj->u.cy->color);
	else
		return (set_color(125,125,200));
}

void	set_intersection(t_ray prim_ray, t_scene scene, t_intersection *inter)
{
	(void)scene;
	inter->color = get_obj_color(inter->obj); 
	inter->p_hit = add(prim_ray.origin, scalar_mult(inter->min_dist, prim_ray.direction));
	inter->norm_hit = get_normal(inter, prim_ray);
	inter->p_hit = add(scalar_mult(ACNEA, inter->norm_hit), inter->p_hit);
}

t_coordinates	get_normal(t_intersection *inter, t_ray prim_ray)
{
	t_coordinates	normal;

	if (inter->obj->type == SPHERE)
		normal = normalized(substract(inter->p_hit, inter->obj->u.sp->centre));
	else if (inter->obj->type == PLANE)
		normal = get_plane_normal(inter->obj->u.pl, prim_ray);
	else if (inter->obj->type == SQUARE)
		normal = get_square_normal(inter->obj->u.sq, prim_ray);
	else if (inter->obj->type == TRIANGLE)
		normal = get_triangle_normal(inter->obj->u.tr, prim_ray);
	else
		normal = set_coordinates(0, 0, 0);
	return (normalized(normal));
}
