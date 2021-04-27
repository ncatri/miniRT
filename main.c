/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 10:39:08 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/27 13:59:53 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/miniRT.h"

int	main(int argc, char **argv)
{
	t_scene		scene;

	if (!check_args(argc, argv))
		return (0);
	scene = scene_extractor(argv[1]);
	if (argc == 2)
		display_something(scene);
	else
	{
		scene.save_bmp = TRUE;
		prepare_output_file(&scene, argv[1]);
		prepare_buffer(&scene);
		ray_tracer(scene);
		create_bitmap(scene);
		free_all(&scene);
	}
}
