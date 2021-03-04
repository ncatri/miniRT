/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:19:21 by ncatrien          #+#    #+#             */
/*   Updated: 2021/03/04 10:49:18 by ncatrien         ###   ########lyon.fr   */
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
	t_light	amb_light;

	split = ft_split(line, ' ');
	if (split_len(split) != 3 || scene->ambient.ratio != -1)
	{
		scene->valid = FALSE;
		free_split(split);
		return ;
	}
	amb_light.ratio = get_ratio(split[1]);
	amb_light.color = get_color(split[2]);
	if (amb_light.ratio == -1 || amb_light.color.value == -1)
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
	camera.position = get_coordinates(split[1]);
	camera.orientation = get_coordinates(split[2]);
	camera.fov = get_fov(split[3]);
	if (camera.position.x == INFINITY || camera.orientation.x == INFINITY || \
camera.fov == -1)
		scene->valid = FALSE;
	ft_lstadd_back(&scene->camera_list, ft_lstnew(&camera));
	free_split(split);
}

void	parse_light(char *line, t_scene *scene)
{
	char	**split;
	t_light	light;

	split = ft_split(line, ' ');
	if (split_len(split) != 4)
	{
		scene->valid = FALSE;
		free_split(split);
		return ;
	}
	light.position = get_coordinates(split[1]);
	light.ratio = get_ratio(split[2]);
	light.color = get_color(split[3]);
	if (light.position.x == INFINITY || light.ratio == -1 || \
light.color.value == -1)
		scene->valid = FALSE;
	scene->light = light;
	free_split(split);
}

void	parse_sphere(char *line, t_scene *scene)
{
	char		**split;
	t_sphere	sphere;

	split = ft_split(line, ' ');
	if (split_len(split) != 4)
	{
		scene->valid = FALSE;
		free_split(split);
		return ;
	}
	sphere.centre = get_coordinates(split[1]);
	sphere.diameter = get_positive_val(split[2]);
	sphere.color = get_color(split[3]);
	if (sphere.centre.x == INFINITY || sphere.diameter == -1 || \
sphere.color.value == -1)
		scene->valid = FALSE;
	scene->sphere = sphere;
	free_split(split);
}
