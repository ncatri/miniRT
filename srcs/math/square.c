#include "../../includes/miniRT.h"

double	intersect_sq(t_square *sq, t_ray ray)
{
	t_plane			sq_plane;
	double			t;
	t_coordinates	hit_point;
	double			bound;
	t_coordinates	hit_vector;

	sq_plane.orientation = sq->orientation;
	sq_plane.position = sq->position;
	t = intersect_pl(&sq_plane, ray);
	if (t != INFINITY)
	{
		bound = sq->side / 2;
		hit_point = add(ray.origin, scalar_mult(t, ray.direction));
		hit_vector = substract(hit_point, sq->position);
		if (fabs(dot(hit_vector, sq->up)) > bound || \
				fabs(dot(hit_vector, sq->right)) > bound)
			return (INFINITY);
	}
	return (t);
}

/*
 * reverse the normal if "back" of square is lighted,
 * in order to get an equal illumination on both faces
 *
*/

t_coordinates	get_square_normal(t_square *square, t_ray ray)
{
	t_coordinates	normal;

	if (dot(ray.direction, square->orientation) > 0)
		normal = scalar_mult(-1, square->orientation);
	else
		normal = square->orientation;
	return (normal);
}	
