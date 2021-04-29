/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:19:21 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/29 12:37:26 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_resolution(char *line, t_scene *scene)
{
	char	**split;

	if (scene->width != 0)
	{
		set_error(scene, E_ALREADY_EXISTS);
		return ;
	}
	split = get_split(line, " \t", 3, scene);
	if (split && scene->valid)
	{
		scene->width = (int)get_positive_val(split[1]);
		scene->height = (int)get_positive_val(split[2]);
		if (scene->width <= 0 || scene->height <= 0)
			set_error(scene, E_INVAL);
		if (scene->width > RESOLUTION_MAX || scene->height > RESOLUTION_MAX)
			set_error(scene, E_IMG_SIZE_MAX);
		if (scene->valid)
			scene->ratio = scene->width / (double)scene->height;
		free_split(split);
	}
	else
		set_error(scene, E_MEM);
}
