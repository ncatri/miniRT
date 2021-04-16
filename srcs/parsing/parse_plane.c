/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:11:45 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/09 10:51:44 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	parse_plane(char *line, t_scene *scene)
{
	char	**split;
	t_plane	*plane;

	split = get_split(line, " \t", 4, scene);
	if (split == NULL)
		return ;
	plane = malloc(sizeof(t_plane));
	if (plane)
	{
		plane->position = get_coordinates(split[1]);
		plane->orientation = get_coordinates(split[2]);
		plane->color = get_color(split[3]);
		if (plane->position.x == INFINITY || plane->orientation.x == INFINITY || \
	plane->color.value == -1)
			set_error(scene, E_INVAL);
		else if (fabs(get_norm2(plane->orientation) - 1) > 0.01)
			set_error(scene, E_NOT_NORMED);
		push_plane_objlist(scene, plane);
	}
	else
		set_error(scene, E_MEM);
	free_split(split);
}

void	push_plane_objlist(t_scene *scene, t_plane *plane)
{
	t_object	*obj;
	t_list		*new;

	obj = malloc(sizeof(t_object));
	if (obj)
	{
		obj->u.pl = plane;
		obj->type = PLANE;
		new = ft_lstnew(obj);
		if (new == NULL)
		{
			set_error(scene, E_MEM);
			return ;
		}
		ft_lstadd_back(&scene->objects_list, new);
	}
	else
		set_error(scene, E_MEM);
}
