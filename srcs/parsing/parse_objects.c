/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:19:21 by ncatrien          #+#    #+#             */
/*   Updated: 2021/03/03 16:51:22 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	parse_resolution(char *line, t_scene *scene)
{
	char	**split;
	int		x;
	int		y;

	split = ft_split(line, ' ');
	if (split_len(split) != 3 || scene->width != 0)
	{
		scene->valid = FALSE;
		free_split(split);
		return ;
	}
	x = ft_atoi(split[1]);
	y = ft_atoi(split[2]);
	if (x <= 0 || y <= 0)
		scene->valid = FALSE;
	scene->width = x;
	scene->height = y;
	free_split(split);
}

void	parse_ambient_light(char *line, t_scene *scene)
{
	char	**split;
	double	ratio;
	t_light	amb_light;

	split = ft_split(line, ' ');
	if (split_len(split) != 3 || scene->ambient.ratio != -1)
	{
		scene->valid = FALSE;
		free_split(split);
		return ;
	}
	ratio = ft_atod(split[1]);
	if (ratio < 0 && ratio > 1)
		scene->valid = FALSE;
	amb_light.ratio = ratio;
	amb_light.color = extract_color(split[2]);
	if (amb_light.color.value < 0)
		scene->valid = FALSE;
	scene->ambient = amb_light;
	free_split(split);
}

void	parse_camera(char *line, t_scene *scene)
{
	char		**split;
	t_camera	camera;

	split = ft_split(line, ' ');
	if (split_len(split) != 4)
	{
		scene->valid = FALSE;
		free_split(split);
		return ;
	}
	camera.position = extract_coordinates(split[1]);
	camera.orientation = extract_coordinates(split[2]);
	if (camera.position.x == INFINITY || camera.orientation.x == INFINITY)
	{
		scene->valid = FALSE;
		free_split(split);
		return ;
	}
	camera.fov = ft_atod(split[3]);
	if (camera.fov < 0 || camera.fov > 180)
		scene->valid = FALSE;
	ft_lstadd_back(&scene->camera_list, ft_lstnew(&camera));
	free_split(split);
}
