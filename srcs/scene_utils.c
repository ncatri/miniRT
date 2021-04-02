/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 10:09:05 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/02 10:09:36 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_bool	iterate_current_light(t_scene *scene)
{
	if (scene && scene->light_list)
	{
		if (scene->cur_light == NULL)
			scene->cur_light = scene->light_list;
		else if (scene->cur_light->next != NULL)
			scene->cur_light = scene->cur_light->next;
		else
			return (FALSE);
		return (TRUE);
	}
	return (FALSE);
}
