/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 14:12:02 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/19 08:40:14 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_image	initialize_image(t_mlx mlx, int width, int height)
{
	t_image	img;

	img.id = mlx_new_image(mlx.connection_graphic_server, width, height);
	img.width = width;
	img.height = height;
	img.address = mlx_get_data_addr(img.id, &img.bits_per_pixel, \
			&img.size_line, &img.endian);
	return (img);
}

void	pixel_put_image(t_image image, int x, int y, t_color color)
{
	char	*dst;

	dst = image.address
		+ (y * image.size_line + x * (image.bits_per_pixel / 8));
	*(unsigned int *)dst = color.value;
}

void	adjust_to_screen_size(t_scene *scene)
{
	int	x;
	int	y;

	mlx_get_screen_size(scene->mlx.connection_graphic_server, &x, &y);
	printf("screen size: %d X %d\n", x, y);
	if (scene->width > x)
		scene->width = x;
	if (scene->height > y)
		scene->height = y;
}
