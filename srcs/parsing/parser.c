/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 13:53:58 by ncatrien          #+#    #+#             */
/*   Updated: 2021/02/26 14:59:51 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_scene	scene_extractor(char *filename)
{
	int fd;
	t_scene	scene;

	fd = open(filename, O_RDONLY);
	if (check_extension(filename) && fd > 0)
	{
		printf("c'est walide!\n");
	}
	else
		printf("nope\n");
	(void)scene;
	exit(0);
}

t_bool	check_extension(char *filename)
{
	int i_dot;

	i_dot = ft_strlen(filename) - 3;
	if (ft_strncmp(&filename[i_dot], ".rt", 3) == 0)
		return (TRUE);
	else
		return (FALSE);
}
