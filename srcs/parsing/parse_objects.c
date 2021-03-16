/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:19:21 by ncatrien          #+#    #+#             */
/*   Updated: 2021/03/16 16:31:00 by ncatrien         ###   ########lyon.fr   */
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

void	parse_ambient_light(char *line, t_scene *scene)
{
	char	**split;
	t_light	amb_light;

	if (scene->ambient.ratio != -1)
	{
		set_error(scene, E_ALREADY_EXISTS);
		return ;
	}
	split = get_split(line, " \t", 3, scene);
	if (split)
	{
		amb_light.ratio = get_ratio(split[1]);
		amb_light.color = get_color(split[2]);
		if (amb_light.ratio == -1 || amb_light.color.value == -1)
			set_error(scene, E_INVAL);
		scene->ambient = amb_light;
		free_split(split);
	}
}

void	parse_camera(char *line, t_scene *scene)
{
	char		**split;
	t_camera	*camera;

	split = get_split(line, " \t", 4, scene);
	if (split == NULL)
		return ;
	camera = malloc(sizeof(t_camera));
	if (camera)
	{
		camera->position = get_coordinates(split[1]);
		camera->orientation = get_coordinates(split[2]);
		camera->fov = get_fov(split[3]);
		set_cameratoworld_matrix(camera);
		if (camera->position.x == INFINITY || camera->orientation.x == INFINITY || \
camera->fov == -1)
			set_error(scene, E_INVAL);
		ft_lstadd_back(&scene->camera_list, ft_lstnew(camera));
	}
	else if (!camera || errno != 0)
		set_error(scene, E_MEM);
	free_split(split);
}

void	parse_light(char *line, t_scene *scene)
{
	char	**split;
	t_light	*light;

	split = get_split(line, " \t", 4, scene);
	if (split == NULL)
		return ;
	light = malloc(sizeof(t_light));
	if (light)
	{
		light->position = get_coordinates(split[1]);
		light->ratio = get_ratio(split[2]);
		light->color = get_color(split[3]);
		if (light->position.x == INFINITY || light->ratio == -1 || \
light->color.value == -1)
			set_error(scene, E_INVAL);
		ft_lstadd_back(&scene->light_list, ft_lstnew(light));
	}
	else if (!light || errno != 0)
		set_error(scene, E_MEM);
	free_split(split);
}

void	parse_sphere(char *line, t_scene *scene)
{
	char		**split;
	t_sphere	*sphere;

	split = get_split(line, " \t", 4, scene);
	if (split == NULL)
		return ;
	sphere = malloc(sizeof(t_sphere));
	if (sphere)
	{
		sphere->centre = get_coordinates(split[1]);
		sphere->diameter = get_positive_val(split[2]);
		sphere->color = get_color(split[3]);
		if (sphere->centre.x == INFINITY || sphere->diameter == -1 || \
sphere->color.value == -1)
			set_error(scene, E_INVAL);
		ft_lstadd_back(&scene->sphere_list, ft_lstnew(sphere));
	}
	else if (!sphere || errno != 0)
		set_error(scene, E_MEM);
	free_split(split);
}
