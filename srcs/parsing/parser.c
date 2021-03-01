/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 13:53:58 by ncatrien          #+#    #+#             */
/*   Updated: 2021/03/01 17:01:54 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_scene	scene_extractor(char *filename)
{
	int		fd;
	t_scene	scene;

	fd = open(filename, O_RDONLY);
	if (check_extension(filename) && fd > 0)
	{
	//	printf("c'est walide!\n");
		scene = parse_file(fd);

	}
	else
	{
		scene.valid = FALSE;
		printf("nope\n");
	}
	return (scene);
}

t_bool	check_extension(char *filename)
{
	int	i_dot;

	i_dot = ft_strlen(filename) - 3;
	if (ft_strncmp(&filename[i_dot], ".rt", 3) == 0)
		return (TRUE);
	else
		return (FALSE);
}

t_scene	parse_file(int fd)
{
	t_scene	scene;
	char	*line;
	int		num_line;

	scene = initialize_scene();
	num_line = 0;
	while (get_next_line(fd, &line) > 0 && scene.valid)
	{
		parse_line(line, &scene);
		num_line++;
		free(line);
	}
	if (scene.valid)
	{
		parse_line(line, &scene);
		if (scene.valid == FALSE)
			printf("Error at line %d.\n", num_line);
		free(line);
	}
	else
		printf("Error at line %d.\n", num_line);
	return (scene);
}

void	parse_line(char *line, t_scene *scene)
{
	if (ft_strncmp(line, "R ", 2) == 0)
		parse_resolution(line, scene);
/*
	else if (ft_strncmp(line, "A ", 2) == 0)
		parse_ambient_light(line, scene);
	else if (ft_strncmp(line, "c ", 2) == 0)
		parse_camera(line, scene);
	else if (ft_strncmp(line, "l ", 2) == 0)
		parse_light(line, scene);
	else if (ft_strncmp(line, "sp ", 3) == 0)
		parse_sphere(line, scene);
	else if (ft_strncmp(line, "pl ", 3) == 0)
		parse_plane(line, scene);
	else if (ft_strncmp(line, "sq ", 3) == 0)
		parse_square(line, scene);
	else if (ft_strncmp(line, "cy ", 3) == 0)
		parse_cylinder(line, scene);
	else if (ft_strncmp(line, "tr ", 3) == 0)
		parse_triangle(line, scene);
*/
	else if (line[0] != '\0' && line[0] != '#')
		scene->valid = FALSE;
}
