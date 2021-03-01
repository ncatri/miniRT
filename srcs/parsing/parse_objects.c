/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:19:21 by ncatrien          #+#    #+#             */
/*   Updated: 2021/03/01 17:01:57 by ncatrien         ###   ########lyon.fr   */
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
		return ;
	}
	x = ft_atoi(split[1]);
	y = ft_atoi(split[2]);
	if (x > 0 && y > 0)
	{
		scene->width = (double)x;
		scene->height = (double)y;
		scene->valid = TRUE;
	}
	else
		scene->valid = FALSE;
	free_split(split);
}

/*
void	parse_ambient_light(char *line, t_scene *scene)
{
	char **split;

	split = ft_split(line, ' ');
	if (split_len(split) != 3 || scene->lightning = 0)
	{
		scene->valid = FALSE;
		return ;
	}
	
*/
