/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:29:21 by ncatrien          #+#    #+#             */
/*   Updated: 2021/03/15 15:30:17 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_coordinates	cross_product(t_coordinates a, t_coordinates b)
{
	t_coordinates	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
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

t_coordinates	set_coordinates(double a, double b, double c)
{
	t_coordinates	result;

	result.x = a;
	result.y = b;
	result.z = c;
	return (result);
}

t_bool	is_equal(t_coordinates a, t_coordinates b)
{
	double	epsilon;

	epsilon = 0.001;
	return (fabs(a.x -b.x) < epsilon && fabs(a.y - b.y) < epsilon
			&& fabs(a.z - b.z) < epsilon);
}

double	**set_cameratoworld_matrix(t_camera camera)
{
	double			**matrix44d;
	t_coordinates	cx;
	t_coordinates	cy;
	t_coordinates	cam_up;

	cam_up = set_coordinates(0, 1, 0);
	if (is_equal(camera.orientation, cam_up) || \
			is_equal(camera.orientation, set_coordinates(0, -1, 0)))
		cam_up = set_coordinates(0, 0, 1);
	cx = cross_product(cam_up, camera.orientation);
	cy = cross_product(camera.orientation, cx);
	matrix44d[0][0] = cx.x;
	matrix44d[0][1] = cx.y;
	matrix44d[0][2] = cx.z;
	matrix44d[0][3] = 0;
	matrix44d[1][0] = cy.x;
	matrix44d[1][1] = cy.y;
	matrix44d[1][2] = cy.z;
	matrix44d[1][3] = 0;
	matrix44d[2][0] = camera.orientation.x;
	matrix44d[2][1] = camera.orientation.y;
	matrix44d[2][2] = camera.orientation.z;
	matrix44d[2][3] = 0;
	matrix44d[3][0] = camera.position.x;
	matrix44d[3][1] = camera.position.y;
	matrix44d[3][2] = camera.position.z;
	matrix44d[3][3] = 1;
	return (matrix44d);
}
	
