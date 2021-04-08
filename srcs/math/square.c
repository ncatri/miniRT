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
		double up_dist = dot(hit_vector, sq->up);
		double right_dist = dot(hit_vector, sq->right);
		if (fabs(up_dist) > bound ||
				fabs(right_dist) > bound)
			return (INFINITY);
	}
	return (t);
}
