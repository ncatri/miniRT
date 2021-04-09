/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:35:16 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/09 13:01:29 by ncatrien         ###   ########lyon.fr   */
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
		else if (obj->type == SQUARE)
			print_square(*(obj->u.sq));
		else if (obj->type == TRIANGLE)
			print_triangle(*(obj->u.tr));
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

void	print_square(t_square sq)
{
	printf("\tposition --> ");
	print_coord(sq.position);
	printf("\torientation --> ");
	print_coord(sq.orientation);
	printf("\tright --> ");
	print_coord(sq.right);
	printf("\tup --> ");
	print_coord(sq.up);
	printf("\tside length --> %.2f\n", sq.side);
	printf("\tcolor --> ");
	print_color(sq.color);
}

void	print_triangle(t_triangle tr)
{
	printf("\tp1 --> ");
	print_coord(tr.p1);
	printf("\tp2 --> ");
	print_coord(tr.p2);
	printf("\tp3 --> ");
	print_coord(tr.p3);
	printf("\tcolor --> ");
	print_color(tr.color);
	printf("\tv12 --> ");
	print_coord(tr.v12);
	printf("\tv23 --> ");
	print_coord(tr.v23);
	printf("\tv31 --> ");
	print_coord(tr.v31);
	printf("\tnormal --> ");
	print_coord(tr.normal);
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
