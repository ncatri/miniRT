/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:35:16 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/28 10:48:33 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_objlist(t_scene scene)
{
	t_list		*cursor;
	int			i;
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
		else if (obj->type == CYLINDER)
			print_cylinder(*(obj->u.cy));
		i++;
		cursor = cursor->next;
	}
	printf("----\n");
}

void	print_cylinder(t_cylinder cy)
{
	printf("\tposition --> ");
	print_coord(cy.position);
	printf("\torientation --> ");
	print_coord(cy.orientation);
	printf("\tdiameter --> %.2f\n", cy.radius * 2);
	printf("\theight --> %.2f\n", cy.height);
	printf("\ttop cap --> \n");
	print_plane(cy.top_cap);
	printf("\tbottom cap --> \n");
	print_plane(cy.bottom_cap);
	printf("\tcolor --> ");
	print_color(cy.color);
}	

void	print_coord(t_coordinates coord)
{
	printf("x: %.2f, y: %.2f, z: %.2f\n", coord.x, coord.y, coord.z);
}

void	print_color(t_color col)
{
	printf("R: %d, G: %d, B: %d\n", col.r, col.g, col.b);
}
