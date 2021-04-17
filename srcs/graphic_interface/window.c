/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 08:06:58 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/17 15:20:33 by ncatrien         ###   ########lyon.fr   */
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
	{
		iter_cur_cam(scene);
		scene->rendered = FALSE;
		mlx_destroy_image(scene->mlx.connection_graphic_server, \
				scene->image.id);
		mlx_clear_window(scene->mlx.connection_graphic_server, \
				scene->mlx.window_id);
		scene->image = initialize_image(scene->mlx, scene->width, \
				scene->height);
	}
	if (key == K_ESC)
	{
		free_all(scene);
		mlx_destroy_window(scene->mlx.connection_graphic_server,
			scene->mlx.window_id);
		exit (0);
	}
	return (0);
}

int	red_cross_quit(t_scene *scene)
{
	free_all(scene);
	mlx_destroy_window(scene->mlx.connection_graphic_server,
		scene->mlx.window_id);
	exit(0);
}

void	display_something(t_scene scene)
{
	set_mlx(&scene);
	check_display_size(&scene);
	mlx_key_hook(scene.mlx.window_id, key_hooks, &scene);
	mlx_hook(scene.mlx.window_id, 17, 0L, red_cross_quit, &scene.mlx);
	scene.image = initialize_image(scene.mlx, scene.width, scene.height);
	mlx_loop_hook(scene.mlx.connection_graphic_server, renderer, &scene);
	mlx_put_image_to_window(scene.mlx.connection_graphic_server, \
			scene.mlx.window_id, scene.image.id, 0, 0);
	display_mouse_position_on_click(scene.mlx);
	mlx_loop(scene.mlx.connection_graphic_server);
}

int	renderer(t_scene *scene)
{
	t_camera	*cam;

	if (scene->rendered == FALSE)
	{
		cam = scene->cur_cam->content;
		print_camera(cam);
		ray_tracer(*scene);
		mlx_put_image_to_window(scene->mlx.connection_graphic_server, \
				scene->mlx.window_id, scene->image.id, 0, 0);
		scene->rendered = TRUE;
	}
	return (1);
}
