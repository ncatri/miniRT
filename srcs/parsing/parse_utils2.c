/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 15:54:44 by ncatrien          #+#    #+#             */
/*   Updated: 2021/03/08 09:01:29 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	set_error(t_scene *scene, char *message)
{
	scene->valid = FALSE;
	scene->err_msg = message;
}

t_bool	is_complete(t_scene scene)
{
	t_bool	ret;
	char*	err_msg;

	ret = TRUE;
	if (scene.width == 0)
	{
		ret = FALSE;
		err_msg = E_NORES;
	}
	else if (scene.ambient.ratio == -1)
	{
		ret = FALSE;
		err_msg = E_NOAMB;
	}
	if (ret == FALSE)
		printf("Error in scene file: %s.\n", err_msg);
	return (ret);
}
