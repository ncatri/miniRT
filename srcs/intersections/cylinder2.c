#include "miniRT.h"

/*
 * Method is from:
 * https://mrl.cs.nyu.edu/~dzorin/rend05/lecture2.pdf
 *
*/

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

double	coef_b(t_cylinder cy, t_ray ray)
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

	delta_p = substract(ray.origin, cy.position);
	tmp_d = dot(delta_p, cy.orientation);
	tmp_v1 = scalar_mult(tmp_d, cy.orientation);
	tmp_v1 = substract(delta_p, tmp_v1);
	tmp_d = dot(tmp_v1, tmp_v1);
	tmp_d = tmp_d - cy.radius * cy.radius;
	return (tmp_d);
}
