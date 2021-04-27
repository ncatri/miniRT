/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:19:21 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/27 13:59:44 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	parse_resolution(char *line, t_scene *scene)
{
	char	**split;
	int		x;
	int		y;

	if (scene->width != 0)
	{
		set_error(scene, E_ALREADY_EXISTS);
		return ;
	}
	split = get_split(line, " \t", 3, scene);
	if (split)
	{
		x = (int)get_positive_val(split[1]);
		y = (int)get_positive_val(split[2]);
		if (x <= 0 || y <= 0)
			set_error(scene, E_INVAL);
		scene->width = x;
		scene->height = y;
		if (scene->valid)
			scene->ratio = x / (double)y;
		free_split(split);
	}
	else
		set_error(scene, E_MEM);
}
