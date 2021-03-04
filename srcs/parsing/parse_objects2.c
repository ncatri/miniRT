/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:11:45 by ncatrien          #+#    #+#             */
/*   Updated: 2021/03/04 11:40:04 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	parse_plane(char *line, t_scene *scene)
{
	char	**split;
	t_plane	plane;

	split = ft_split(line, ' ');
	if (split_len(split) != 4)
	{
		scene->valid = FALSE;
		free_split(split);
		return ;
	}
	plane.position = get_coordinates(split[1]);
	plane.orientation = get_coordinates(split[2]);
	plane.color = get_color(split[3]);
	if (plane.position.x == INFINITY || plane.orientation.x == INFINITY || \
plane.color.value == -1)
		scene->valid = FALSE;
	ft_lstadd_back(&scene->plane_list, ft_lstnew(&plane));
	free_split(split);
}
