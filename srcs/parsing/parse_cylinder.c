#include "../../includes/miniRT.h"

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
		cy->position = get_coordinates(split[1]);
		cy->orientation = get_coordinates(split[2]);
		cy->diameter = get_positive_val(split[3]);
		cy->height = get_positive_val(split[4]);
		cy->color = get_color(split[5]);
		if (cy->position.x == INFINITY || cy->orientation.x == INFINITY \
	|| cy->diameter == -1 || cy->height == -1 || cy->color.value == -1)
			set_error(scene, E_INVAL);
		else if (fabs(get_norm2(cy->orientation) - 1) > 0.01)
			set_error(scene, E_NOT_NORMED);
		push_cylinder_objlist(scene, cy);
	}
	else
		set_error(scene, E_MEM);
	free_split(split);
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
