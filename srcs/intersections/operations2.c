/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:29:21 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/28 10:48:33 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_coordinates	cross_product(t_coordinates a, t_coordinates b)
{
	t_coordinates	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

t_coordinates	mult_vec_matrix(double mat[4][4], t_coordinates vec)
{
	t_coordinates	res;

	res.x = vec.x * mat[0][0] + vec.y * mat[1][0] + vec.z * mat[2][0];
	res.y = vec.x * mat[0][1] + vec.y * mat[1][1] + vec.z * mat[2][1];
	res.z = vec.x * mat[0][2] + vec.y * mat[1][2] + vec.z * mat[2][2];
	return (res);
}

t_coordinates	scalar_mult(double k, t_coordinates vect)
{
	t_coordinates	res;

	res.x = k * vect.x;
	res.y = k * vect.y;
	res.z = k * vect.z;
	return (res);
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
	return (fabs(a.x -b.x) < epsilon && fabs(a.y - b.y) < epsilon \
			&& fabs(a.z - b.z) < epsilon);
}
