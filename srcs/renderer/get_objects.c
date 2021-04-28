#include "miniRT.h"

double	get_obj_intersect(t_object *obj, t_ray ray)
{
	if (obj->type == SPHERE)
		return (intersect_sp(obj->u.sp, ray));
	else if (obj->type == PLANE)
		return (intersect_pl(obj->u.pl, ray));
	else if (obj->type == SQUARE)
		return (intersect_sq(obj->u.sq, ray));
	else if (obj->type == TRIANGLE)
		return (intersect_tr(obj->u.tr, ray));
	else if (obj->type == CYLINDER)
		return (intersect_cy(obj->u.cy, ray));
	else
		return (INFINITY);
}

t_color	get_obj_color(t_object *obj)
{
	if (obj->type == SPHERE)
		return (obj->u.sp->color);
	else if (obj->type == PLANE)
		return (obj->u.pl->color);
	else if (obj->type == SQUARE)
		return (obj->u.sq->color);
	else if (obj->type == TRIANGLE)
		return (obj->u.tr->color);
	else if (obj->type == CYLINDER)
		return (obj->u.cy->color);
	else
		return (set_color(125, 125, 200));
}

t_coordinates	get_normal(t_intersection *inter, t_ray prim_ray)
{
	t_coordinates	normal;

	if (inter->obj->type == SPHERE)
		normal = normalized(substract(inter->p_hit, inter->obj->u.sp->centre));
	else if (inter->obj->type == PLANE)
		normal = get_plane_normal(inter->obj->u.pl, prim_ray);
	else if (inter->obj->type == SQUARE)
		normal = get_square_normal(inter->obj->u.sq, prim_ray);
	else if (inter->obj->type == TRIANGLE)
		normal = get_triangle_normal(inter->obj->u.tr, prim_ray);
	else if (inter->obj->type == CYLINDER)
		normal = get_cylinder_normal(inter->obj->u.cy, prim_ray, inter);
	else
		normal = set_coordinates(0, 0, 0);
	return (normalized(normal));
}
