#include "../../includes/miniRT.h"

/*
 * Method is from:
 * https://mrl.cs.nyu.edu/~dzorin/rend05/lecture2.pdf
 *
*/

double	intersect_cy(t_cylinder *cy, t_ray ray)
{
	t_polynome2deg	poly;

	poly = solve_infinite_cy(cy, ray);
	if (poly.delta < 0 || poly.sol1 < 0)
		return (INFINITY);
	check_if_between_planes(&poly.sol1, cy, ray);
	check_if_between_planes(&poly.sol2, cy, ray);
	check_if_hit_caps(&poly.sol1, cy, ray);
	check_if_hit_caps(&poly.sol2, cy, ray);
	return (fmin(poly.sol1, poly.sol2));
}

void	check_if_between_planes(double	*t, t_cylinder *cy, t_ray ray)
{
	t_coordinates	hit;
	double			proj;

	hit = add(ray.origin, scalar_mult(*t, ray.direction));
	hit = substract(hit, cy->position);
	proj = dot(hit, cy->orientation);
	if (proj < 0 || proj > cy->height)
		*t = INFINITY;
}

void	check_if_hit_caps(double *t, t_cylinder *cy, t_ray ray)
{
	double			t_top_cap;
	double			t_bottom_cap;
	t_coordinates	hit_top;
	t_coordinates	hit_bottom;

	t_top_cap = intersect_pl(&cy->top_cap, ray);
	hit_top = add(ray.origin, scalar_mult(t_top_cap, ray.direction));
	if (get_norm2(substract(hit_top, cy->top_cap.position)) \
			> cy->radius * cy->radius)
		t_top_cap = INFINITY;
	t_bottom_cap = intersect_pl(&cy->bottom_cap, ray);
	hit_bottom = add(ray.origin, scalar_mult(t_bottom_cap, ray.direction));
	if (get_norm2(substract(hit_bottom, cy->bottom_cap.position)) \
			> cy->radius * cy->radius)
		t_bottom_cap = INFINITY;
	if (t_top_cap < *t || t_bottom_cap < *t)
		*t = fmin(t_top_cap, t_bottom_cap);
}	

t_coordinates	get_cylinder_normal(t_cylinder *cy, t_ray ray,
		t_intersection *inter)
{
	t_coordinates	normal;
	t_coordinates	hit_vec;
	t_coordinates	axis_proj_vec;
	double			proj;
	double			n;

	hit_vec = substract(inter->p_hit, cy->position);
	proj = dot(cy->orientation, hit_vec);
	axis_proj_vec = add(cy->position, scalar_mult(proj, cy->orientation));
	n = get_norm2(substract(inter->p_hit, axis_proj_vec));
	if (fabs(n - cy->radius * cy->radius) < PRECISION)
		normal = normalized(substract(inter->p_hit, axis_proj_vec));
	else
		normal = get_plane_normal(&cy->top_cap, ray);
	return (normal);
}

t_polynome2deg	solve_infinite_cy(t_cylinder *cy, t_ray ray)
{
	t_polynome2deg	poly;

	poly.a = coef_a(*cy, ray);
	poly.b = coef_b(*cy, ray);
	poly.c = coef_c(*cy, ray);
	poly.delta = poly.b * poly.b - 4 * poly.a * poly.c;
	if (poly.delta >= 0)
	{
		poly.sol1 = (-poly.b + sqrt(poly.delta)) / (2 * poly.a);
		poly.sol2 = (-poly.b - sqrt(poly.delta)) / (2 * poly.a);
	}
	return (poly);
}
