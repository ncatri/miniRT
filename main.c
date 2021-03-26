/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 10:39:08 by ncatrien          #+#    #+#             */
/*   Updated: 2021/03/26 15:07:14 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/miniRT.h"

int main(int argc, char **argv)
{
	if (!check_args(argc, argv))
		return (0);

	t_scene		scene;
	scene = scene_extractor(argv[1]);
/*
	t_camera *cam = scene.cur_cam->content;
	print_camera(cam);
	t_coordinates vec = set_coordinates(1, 0, 0);
	vec = mult_vec_matrix(cam->c2w_matrix, vec);
	print_coord(vec);
*/
	print_coord(scene.ambient.intensity);
	display_something(scene);
}
