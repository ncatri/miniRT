/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 13:15:35 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/17 13:25:19 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	split_len(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		;
	return (i);
}

char	**get_split(char *line, char *sep, int size, t_scene *scene)
{
	char	**split;

	split = ft_split(line, sep);
	if (split == NULL)
	{
		set_error(scene, E_MEM);
		return (NULL);
	}
	else if (split_len(split) != size)
	{
		set_error(scene, E_NUM_ELEMT);
		free_split(split);
		return (NULL);
	}
	else
		return (split);
}

t_scene	initialize_scene(void)
{
	t_scene	scene;

	scene.rendered = FALSE;
	scene.width = 0;
	scene.height = 0;
	scene.ambient.ratio = -1;
	scene.camera_list = NULL;
	scene.cur_cam = NULL;
	scene.light_list = NULL;
	scene.cur_light = NULL;
	scene.objects_list = NULL;
	scene.valid = TRUE;
	return (scene);
}

t_bool	str_isnumber(const char *str)
{
	t_bool	dot_flag;

	dot_flag = TRUE;
	if (*str == '-')
		str++;
	while (*str)
	{
		if (*str == '.' && dot_flag)
			dot_flag = FALSE;
		else if (!ft_isdigit(*str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}
