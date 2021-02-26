/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 08:21:06 by ncatrien          #+#    #+#             */
/*   Updated: 2021/02/25 13:48:49 by ncatrien         ###   ########lyon.fr   */
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

t_ray	primary_ray(double x, double y, t_scene scene)
{
	t_ray	ray;

	x = x - scene.width / 2;
	y = y - scene.height / 2;

	ray.direction.x = x - scene.camera.position.x / 2;
	ray.direction.y = y - scene.camera.position.y / 2;
	ray.direction.z = scene.width / \
					  (2 * tan(scene.camera.fov * M_PI / (2 * 180)));
	ray.origin = scene.camera.position;
	return (ray);
}
