/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 13:15:35 by ncatrien          #+#    #+#             */
/*   Updated: 2021/03/01 17:02:00 by ncatrien         ###   ########lyon.fr   */
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
//	scene.lightning = 0;
	scene.valid = TRUE;
	return (scene);
}
