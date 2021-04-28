/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 15:54:44 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/28 15:36:40 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	{
		ft_putstr_fd("Error in scene file: ", 2);
		ft_putstr_fd(scene->err_msg, 2);
		ft_putstr_fd(".\n", 2);
	}
	return (scene->valid);
}

void	display_error_line(int num_line, char *msg)
{
	ft_putstr_fd("Error\nLine ", 2);
	ft_putnbr_fd(num_line, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(".\n", 2);
}
