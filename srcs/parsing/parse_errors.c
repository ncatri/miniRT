/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 15:54:44 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/28 08:47:42 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	set_error(t_scene *scene, char *message)
{
	if (scene->valid)
	{
		scene->valid = FALSE;
		scene->err_msg = message;
	}
}

t_bool	check_complete(t_scene *scene)
{
	if (scene->width == 0)
		set_error(scene, E_NORES);
	else if (scene->ambient.ratio == -1)
		set_error(scene, E_NOAMB);
	else if (scene->camera_list == NULL)
		set_error(scene, E_NOCAM);
	if (scene->valid == FALSE)
		printf("Error in scene file: %s.\n", scene->err_msg);
	return (scene->valid);
}
