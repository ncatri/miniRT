/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 10:39:08 by ncatrien          #+#    #+#             */
/*   Updated: 2021/03/19 15:29:14 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/miniRT.h"

int main(int argc, char **argv)
{
	if (!check_args(argc, argv))
		return (0);

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

	display_something(scene);
}
