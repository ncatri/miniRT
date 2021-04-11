#include "../../includes/miniRT.h"

double	intersect_cy(t_cylinder *cy, t_ray ray)
{
	t_polynome2deg	poly;
	
	poly.a = coef_a(*cy, ray);
	poly.b = coef_b(*cy, ray);
	poly.c = coef_c(*cy, ray);
	poly.delta = poly.b * poly.b - 4 * poly.a * poly.c;
	if (poly.delta < 0)
		return (INFINITY);
	poly.sol1 = (-poly.b + sqrt(poly.delta)) / (2 * poly.a);
	poly.sol2 = (-poly.b - sqrt(poly.delta)) / (2 * poly.a);
	if (poly.sol1 < 0)
		return (INFINITY);
	if (poly.sol2 > 0)
		return (poly.sol2);
	else
		return (poly.sol1);
}

double	coef_a(t_cylinder cy, t_ray ray)
{
	double			tmp_d;
	t_coordinates	tmp_v;

	tmp_d = dot(ray.direction, cy.orientation);
	tmp_v = scalar_mult(tmp_d, cy.orientation);
	tmp_v = substract(ray.direction, tmp_v);
	tmp_d = dot(tmp_v, tmp_v);
	return (tmp_d);
}

double coef_b(t_cylinder cy, t_ray ray)
{
	double			tmp_d;
	t_coordinates	tmp_v;
	t_coordinates	delta_p;
	t_coordinates	tmp_v2;


	tmp_d = dot(ray.direction, cy.orientation);
	tmp_v = scalar_mult(tmp_d, cy.orientation);
	tmp_v = substract(ray.direction, tmp_v);
	
	delta_p = substract(ray.origin, cy.position);
	tmp_d = dot(delta_p, cy.orientation);
	tmp_v2 = scalar_mult(tmp_d, cy.orientation);
	tmp_v2 = substract(delta_p, tmp_v2);
	tmp_d = 2 * dot(tmp_v, tmp_v2);
	return (tmp_d);
}

double	coef_c(t_cylinder cy, t_ray ray)
{
	double			tmp_d;
	t_coordinates	tmp_v1;
	t_coordinates	delta_p;

	delta_p = substract(ray.origin, cy.orientation);
	tmp_d = dot(delta_p, cy.orientation);
	tmp_v1 = scalar_mult(tmp_d, cy.orientation);
	tmp_v1 = substract(delta_p, tmp_v1);
	tmp_d = dot(tmp_v1, tmp_v1);
	tmp_d = tmp_d - cy.diameter * cy.diameter;
	return (tmp_d);
}
