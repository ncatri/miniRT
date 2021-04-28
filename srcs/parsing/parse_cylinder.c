#include "miniRT.h"

void	parse_cylinder(char *line, t_scene *scene)
{
	char		**split;
	t_cylinder	*cy;

	split = get_split(line, " \t", 6, scene);
	if (split == NULL)
		return ;
	cy = malloc(sizeof(t_cylinder));
	if (cy)
	{
		fill_cylinder_values(cy, split);
		check_cylinder_values(cy, scene);
		if (scene->valid)
			complete_cylinder_values(cy);
		push_cylinder_objlist(scene, cy);
	}
	else
		set_error(scene, E_MEM);
	free_split(split);
}

void	complete_cylinder_values(t_cylinder *cy)
{
	cy->top_cap.position = add(cy->position,
			scalar_mult(cy->height, cy->orientation));
	cy->top_cap.orientation = cy->orientation;
	cy->bottom_cap.position = cy->position;
	cy->bottom_cap.orientation = cy->orientation;
}

void	fill_cylinder_values(t_cylinder *cy, char **split)
{
	if (!cy || !split)
		return ;
	cy->position = get_coordinates(split[1]);
	cy->orientation = get_unit_coordinates(split[2]);
	cy->radius = get_positive_val(split[3]) / 2;
	cy->height = get_positive_val(split[4]);
	cy->color = get_color(split[5]);
}

void	check_cylinder_values(t_cylinder *cy, t_scene *scene)
{
	if (!cy || !scene)
	{
		set_error(scene, E_MEM);
		return ;
	}
	if (cy->position.x == INFINITY
		|| cy->orientation.x == INFINITY
		|| cy->radius < 0
		|| cy->height == -1
		|| cy->color.value == -1)
		set_error(scene, E_INVAL);
	else
		cy->orientation = normalized(cy->orientation);
}

void	push_cylinder_objlist(t_scene *scene, t_cylinder *cy)
{
	t_object	*obj;
	t_list		*new;

	obj = malloc(sizeof(t_object));
	if (obj)
	{
		obj->type = CYLINDER;
		obj->u.cy = cy;
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
