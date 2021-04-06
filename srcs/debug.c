/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:35:16 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/06 09:15:26 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	print_objlist(t_scene scene)
{
	t_list *cursor;
	int		i;
	t_object	*obj;

	i = 1;
	printf("objects list:\n");
	cursor = scene.objects_list;
	while (cursor)
	{
		obj = cursor->content;
		printf("elt number: %d, type: %d\n", i, obj->type);
		if (obj->type == SPHERE)
			print_sphere(*(obj->u.sp));	
		else if (obj->type == PLANE)
			print_plane(*(obj->u.pl));
		i++;
		cursor = cursor->next;
	}
	printf("----\n");
}

void	print_sphere(t_sphere sp)
{
	printf("\tposition --> ");
	print_coord(sp.centre);
	printf("\tdiameter --> %.2f\n", sp.diameter);
	printf("\tcolor --> ");
	print_color(sp.color);
}

void print_plane(t_plane pl)
{
	printf("\tposition --> ");
	print_coord(pl.position);
	printf("\torientation --> ");
	print_coord(pl.orientation);
	printf("\tcolor --> ");
	print_color(pl.color);
}

void	print_camera(t_camera *cam)
{
	printf("----camera----\n");
	printf("\tposition --> ");
	print_coord(cam->position);
	printf("\torientation --> ");
	print_coord(cam->orientation);
	printf("\tfov --> ");
	printf("%.1f\n", cam->fov);
	print_matrix44d(cam->c2w_matrix);
	printf("----\n");
}
	

void	print_coord(t_coordinates coord)
{
	printf("x: %.2f, y: %.2f, z: %.2f\n", coord.x, coord.y, coord.z);
}

void	print_color(t_color col)
{
	printf("R: %d, G: %d, B: %d\n", col.r, col.g, col.b);
}

void	print_matrix44d(double matrix[4][4])
{
	int i;
	int j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		printf("| ");
		while (++j < 4)
			printf("%4.2f ", matrix[i][j]);
		printf("|\n");
	}
}
