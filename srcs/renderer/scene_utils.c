/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 10:09:05 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/28 10:41:32 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

void	free_all(t_scene *scene)
{
	ft_lstclear(&scene->camera_list, free);
	ft_lstclear(&scene->light_list, free);
	ft_lstclear(&scene->objects_list, free_obj);
	if (scene->image_buffer)
		free(scene->image_buffer);
}

void	free_obj(void *content)
{
	t_object	*obj;

	obj = content;
	free(obj->u.tr);
	free(content);
}

int	iter_cur_cam(t_scene *scene)
{
	if (scene->camera_list == NULL || scene->cur_cam == NULL)
		return (0);
	if (scene->cur_cam->next == NULL)
		scene->cur_cam = scene->camera_list;
	else
		scene->cur_cam = scene->cur_cam->next;
	return (1);
}

void	exit_cleanly_with_message(t_scene *scene, int exit_code, char *message)
{
	free_all(scene);
	ft_putstr_fd("Error:\n", 2);
	ft_putstr_fd(message, 2);
	exit(exit_code);
}
