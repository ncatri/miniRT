/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 08:21:06 by ncatrien          #+#    #+#             */
/*   Updated: 2021/03/15 09:36:53 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	ray_tracer(t_image image, t_scene scene)
{
	int i;
	int j;
	t_ray	ray;

	(void)image;

	i = 0;
	while (i < scene.width)
	{
		j = 0;
		while (j < scene.height)
		{
			ray = primary_ray(i, j, scene);
			ray.direction = normalized(ray.direction);
			if (intersect_sp(scene.sphere, ray))
				pixel_put_image(image, i, j, scene.sphere.color.value); 
			else
				pixel_put_image(image, i, j, 16777215); 
			j++;
		}
		i++;
	}
}

t_ray	primary_ray(int	x, int y, t_scene scene)
{
	t_ray	ray;

	x = x - scene.width / 2;
	y = scene.height / 2 - y;

//	ray direction in the camera base
	ray.direction.x = scene.camera.position.x / 2 - x;
	ray.direction.y = y - scene.camera.position.y / 2;
	ray.direction.z = scene.width / \
					  (2 * tan(scene.camera.fov * M_PI / (2 * 180)));

	ray.origin = scene.camera.position;
	return (ray);
}

/*
t_ray	primary_ray(int x, int y, t_scene scene)
{
	t_ray	ray;

	x = (x + 0.5) / scene.width;
	y = (y + 0.5) / scene.height;

	x = (2 * x - 1) * scene.ratio;
	y = 1 - 2 * y;

	x = x * tan(scene.camera.fov * M_PI / (2 * 180));
	y = y * tan(scene.camera.fov * M_PI / (2 * 180));

	ray.direction.x = x - scene.camera.position.x;
	ray.direction.y = y - scene.camera.position.y;
	ray.direction.z = -1;
	ray.origin = scene.camera.position;
	return (ray);
}
*/
