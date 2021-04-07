#include "../../includes/miniRT.h"

double	intersect_sq(t_square *sq, t_ray ray)
{
	t_plane			sq_plane;
	double			t;
	t_coordinates	hit;
	double			bound;

	sq_plane.orientation = sq->orientation;
	sq_plane.position = sq->position;
	t = intersect_pl(&sq_plane, ray);
	if (t != INFINITY)
	{
		bound = sq->side / 2;
		hit = add(ray.origin, scalar_mult(t, ray.direction));
		hit = substract(hit, sq->position);
		if (fabs(hit.x) > bound || fabs(hit.y) > bound) 
			return (INFINITY);
	}
	return (t);
}
