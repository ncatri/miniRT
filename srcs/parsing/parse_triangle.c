#include "miniRT.h"

void	parse_triangle(char *line, t_scene *scene)
{
	char		**split;
	t_triangle	*triangle;

	split = get_split(line, " \t", 5, scene);
	if (split == NULL)
		return ;
	triangle = malloc(sizeof(t_triangle));
	if (triangle)
	{
		triangle->p1 = get_coordinates(split[1]);
		triangle->p2 = get_coordinates(split[2]);
		triangle->p3 = get_coordinates(split[3]);
		triangle->color = get_color(split[4]);
		if (triangle->p1.x == INFINITY || triangle->p2.x == INFINITY || \
	triangle->p3.x == INFINITY || triangle->color.value == -1)
			set_error(scene, E_INVAL);
		set_triangle_vectors(triangle);
		push_triangle_objlist(scene, triangle);
	}
	else
		set_error(scene, E_MEM);
	free_split(split);
}

void	set_triangle_vectors(t_triangle *tr)
{
	tr->v12 = substract(tr->p2, tr->p1);
	tr->v23 = substract(tr->p3, tr->p2);
	tr->v31 = substract(tr->p1, tr->p3);
	tr->normal = normalized(cross_product(tr->v12, tr->v23));
}

void	push_triangle_objlist(t_scene *scene, t_triangle *triangle)
{
	t_object	*obj;
	t_list		*new;

	obj = malloc(sizeof(t_object));
	if (obj)
	{
		obj->u.tr = triangle;
		obj->type = TRIANGLE;
		new = ft_lstnew(obj);
		if (new == NULL)
		{
			set_error(scene, E_MEM);
			return ;
		}
		ft_lstadd_back(&scene->objects_list, new);
	}
	else
		set_error(scene, E_MEM);
}
