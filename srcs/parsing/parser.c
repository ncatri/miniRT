/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 13:53:58 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/28 08:10:29 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_bool	check_args(int argc, char **argv)
{
	t_bool	check;

	check = TRUE;
	if (argc < 2 || argc > 3)
		check = FALSE;
	else if (!check_extension(argv[1]))
	{
		printf("Error\nInvalid file extension\t");
		check = FALSE;
	}
	else if (argc == 3 && ft_strcmp(argv[2], "--save") != 0)
	{
		printf("Error\nUnknown option\t");
		check = FALSE;
	}
	if (check == FALSE)
		printf("Usage: ./miniRT *file*.rt [--save]\n");
	return (check);
}

t_scene	scene_extractor(char *filename)
{
	int		fd;
	t_scene	scene;

	fd = open(filename, O_RDONLY);
	if (fd > 0)
		scene = parse_file(fd);
	else
	{
		scene.valid = FALSE;
		printf("Error\nCan't open file %s.\n", filename);
	}
	close(fd);
	if (!scene.valid || !check_complete(&scene))
	{
		free_all(&scene);
		exit(1);
	}
	return (scene);
}

t_bool	check_extension(char *filename)
{
	int	i_dot;

	i_dot = ft_strlen(filename) - 3;
	if (ft_strcmp(&filename[i_dot], ".rt") == 0)
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
		num_line++;
	}
	if (!scene.valid)
		printf("Error\nLine %d: %s\n", num_line, scene.err_msg);
	free(line);
	return (scene);
}

void	parse_line(char *line, t_scene *scene)
{
	char	*str;

	str = line;
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	if (ft_strncmp(str, "R", 1) == 0)
		parse_resolution(str, scene);
	else if (ft_strncmp(str, "A", 1) == 0)
		parse_ambient_light(str, scene);
	else if (ft_strncmp(str, "cy", 2) == 0)
		parse_cylinder(str, scene);
	else if (ft_strncmp(str, "c", 1) == 0)
		parse_camera(str, scene);
	else if (ft_strncmp(str, "l", 1) == 0)
		parse_light(str, scene);
	else if (ft_strncmp(str, "sp", 2) == 0)
		parse_sphere(str, scene);
	else if (ft_strncmp(str, "pl", 2) == 0)
		parse_plane(str, scene);
	else if (ft_strncmp(str, "sq", 2) == 0)
		parse_square(str, scene);
	else if (ft_strncmp(str, "tr", 2) == 0)
		parse_triangle(str, scene);
	else if (line[0] != '\0' && line[0] != '#' && str[0] != '#')
		set_error(scene, E_BADLINE);
}
