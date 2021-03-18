/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 10:39:08 by ncatrien          #+#    #+#             */
/*   Updated: 2021/03/18 16:02:38 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/miniRT.h"
/*
int	fct(int key, t_mlx *mlx)
{
	if (key == 8)
		printf("in hook, key: %d\n", key);
	if (key == 53)
	{
//		free_all(*scene);
		mlx_destroy_window(mlx->connection_graphic_server, mlx->window_id);
	}
	
	return (0);
}

int	iter_camera(int key, void *param)
{
	if (key == 124)
		printf("iter_camera\n");
	(void)param;
	return (0);
}
*/
int main(int argc, char **argv)
{
	if (!check_args(argc, argv))
		return (0);

	t_window	window;
	t_mlx		mlx;
	t_image		img;
	t_scene		scene;
	t_camera	camera;
	t_sphere	sphere;

	scene = scene_extractor(argv[1]);
	print_objlist(scene);

	camera.position.x = 0;
	camera.position.y = 0;
	camera.position.z = 0;
	camera.fov = 60;
	camera.orientation.x = 0;
	camera.orientation.y = 0;
	camera.orientation.z = 1;
	set_cameratoworld_matrix(&camera);
	print_matrix44d(camera.c2w_matrix);

	scene.camera = camera;
	scene.width = 1000;
	scene.height = 800;

	sphere.centre.x = 20;
	sphere.centre.y = 20;
	sphere.centre.z = 100;
	sphere.diameter = 50;
	sphere.color.r = 255;
	sphere.color.g = 0;	
	sphere.color.b = 0;	
	sphere.color.value = create_trgb(sphere.color);

	scene.sphere = sphere;

	window = define_window(1000, 800, "this is a test window");
	mlx = initialize_mlx(window);
	img.id = mlx_new_image(mlx.connection_graphic_server, 1000, 800);
	img = initialize_image(mlx, 1000, 800);
	if (mlx.checks)
	{
		ray_tracer(img, scene);
		mode_quit_on_click_red_cross(mlx);
		mode_quit_on_esc(mlx);
		mlx_put_image_to_window(mlx.connection_graphic_server, mlx.window_id, 
		img.id, 0, 0);
	//	mlx_destroy_image(mlx.connection_graphic_server, img.id);
		mlx_loop(mlx.connection_graphic_server);
	}
	else
		return (1);
}
