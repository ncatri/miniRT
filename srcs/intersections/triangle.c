#include "../../includes/miniRT.h"

double	intersect_tr(t_triangle *tr, t_ray ray)
{
	t_plane			tr_plane;
	double			t;
	t_coordinates	hit_point;

	tr_plane.position = tr->p3;
	tr_plane.orientation = tr->normal;
	t = intersect_pl(&tr_plane, ray);
	if (t != INFINITY)
	{
		hit_point = add(ray.origin, scalar_mult(t, ray.direction));
		if (is_hit_inside_triangle(hit_point, tr))
			return (t);
	}
	return (INFINITY);
}

t_bool	is_hit_inside_triangle(t_coordinates point, t_triangle *tr)
{
	t_coordinates	c1;
	t_coordinates	c2;
	t_coordinates	c3;

	c1 = substract(point, tr->p1);
	c2 = substract(point, tr->p2);
	c3 = substract(point, tr->p3);
	if (dot(tr->normal, cross_product(tr->v12, c1)) > 0
		&& dot(tr->normal, cross_product(tr->v23, c2)) > 0
		&& dot(tr->normal, cross_product(tr->v31, c3)) > 0)
		return (TRUE);
	else
		return (FALSE);
}

t_coordinates	get_triangle_normal(t_triangle *triangle, t_ray ray)
{
	t_coordinates	normal;

	if (dot(ray.direction, triangle->normal) > 0)
		normal = scalar_mult(-1, triangle->normal);
	else
		normal = triangle->normal;
	return (normal);
}
