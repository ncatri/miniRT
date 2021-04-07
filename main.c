/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 10:39:08 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/07 12:11:47 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/miniRT.h"

int main(int argc, char **argv)
{
	if (!check_args(argc, argv))
		return (0);

	t_scene		scene;
	scene = scene_extractor(argv[1]);

	t_camera *cam = scene.cur_cam->content;
	print_camera(cam);
	print_objlist(scene);
	
	print_coord(scene.ambient.intensity);
	display_something(scene);
}
