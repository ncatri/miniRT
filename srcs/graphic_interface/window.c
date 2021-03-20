/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 08:06:58 by ncatrien          #+#    #+#             */
/*   Updated: 2021/03/19 15:29:44 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	set_mlx(t_scene *scene)
{
	scene->mlx.connection_graphic_server = mlx_init();
	scene->mlx.window_id = mlx_new_window(scene->mlx.connection_graphic_server,
			scene->width, scene->height, WINDOW_TITLE);
	if (!scene->mlx.connection_graphic_server || !scene->mlx.window_id)
		set_error(scene, "couille mlx\n");
}

int	key_hooks(int key, t_scene *scene)
{
	if (key == K_C)
		printf("iter_cam goes here.\n");
	if (key == K_ESC)
	{
		free_all(scene);
		mlx_destroy_window(scene->mlx.connection_graphic_server,
			scene->mlx.window_id);
		exit (0);
	}
	return (0);
}

int	red_cross_quit(int key, t_scene *scene)
{
	(void)key;
	(void)scene;
	free_all(scene); //segfault
	exit(0);
}

void	display_something(t_scene scene)
{
	t_image image;

	set_mlx(&scene);
	mlx_key_hook(scene.mlx.window_id, key_hooks, &scene);
	mlx_hook(scene.mlx.window_id, 17, 0, red_cross_quit, &scene.mlx);
	image = initialize_image(scene.mlx, scene.width, scene.height);
	ray_tracer(image, scene);
	mlx_put_image_to_window(scene.mlx.connection_graphic_server, scene.mlx.window_id, image.id, 0, 0);
	mlx_loop(scene.mlx.connection_graphic_server);
}
