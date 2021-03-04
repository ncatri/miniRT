/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 13:15:35 by ncatrien          #+#    #+#             */
/*   Updated: 2021/03/04 10:11:33 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	split_len(char **split)
{
	int i;

	i = -1;
	while (split[++i])
		;
	return (i);
}

t_scene	initialize_scene(void)
{
	t_scene	scene;

	scene.width = 0;
	scene.height = 0;
	scene.ambient.ratio = -1;
	scene.valid = TRUE;
	scene.camera_list = NULL;
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
