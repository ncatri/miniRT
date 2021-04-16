/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:19:21 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/06 09:08:43 by ncatrien         ###   ########lyon.fr   */
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
		scene->err_msg = E_ALREADY_EXISTS;
		scene->valid = FALSE;
		return ;
	}
	split = get_split(line, " \t", 3, scene);
	if (split)
	{
		x = (int)get_positive_val(split[1]);
		y = (int)get_positive_val(split[2]);
		if (x == -1 || y == -1)
		{
			scene->valid = FALSE;
			scene->err_msg = E_INVAL;
		}
		scene->width = x;
		scene->height = y;
		scene->ratio = x / (double)y;
		free_split(split);
	}
}
