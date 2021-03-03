/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_extractors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 08:55:06 by ncatrien          #+#    #+#             */
/*   Updated: 2021/03/03 16:51:18 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_color	extract_color(char *data)
{
	char	**extract;
	t_color	color;

	extract = ft_split(data, ',');
	if (split_len(extract) != 3 || !str_isnumber(extract[0]) || \
!str_isnumber(extract[1]) || !str_isnumber(extract[2]))
	{
		color.value = -1;
		free_split(extract);
		return (color);
	}
	color.r = ft_atoi(extract[0]);
	color.g = ft_atoi(extract[1]);
	color.b = ft_atoi(extract[2]);
	if (valid_rgb(color))
		color.value = create_trgb(color);
	else
		color.value = -1;
	free_split(extract);
	return (color);
}

t_bool	valid_rgb(t_color color)
{
	if (color.r < 0 || color.r > 255 || color.g < 0 || color.g > 255 || \
color.b < 0 || color.b > 255)
		return (FALSE);
	return (TRUE);
}

t_coordinates	extract_coordinates(char *data)
{
	char			**extract;
	t_coordinates	coord;

	extract = ft_split(data, ',');
	if (split_len(extract) != 3 || !str_isnumber(extract[0]) || \
!str_isnumber(extract[1]) || !str_isnumber(extract[2]))
		coord.x = INFINITY;
	else
	{
		coord.x = ft_atod(extract[0]);
		coord.y = ft_atod(extract[1]);
		coord.z = ft_atod(extract[2]);
	}
	free_split(extract);
	return (coord);
}
