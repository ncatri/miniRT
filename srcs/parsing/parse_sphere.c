#include "../../includes/miniRT.h"

void	parse_sphere(char *line, t_scene *scene)
{
	char		**split;
	t_sphere	*sphere;

	split = get_split(line, " \t", 4, scene);
	if (split == NULL)
		return ;
	sphere = malloc(sizeof(t_sphere));
	if (sphere)
	{
		sphere->centre = get_coordinates(split[1]);
		sphere->diameter = get_positive_val(split[2]);
		sphere->color = get_color(split[3]);
		if (sphere->centre.x == INFINITY || sphere->diameter == -1 || \
sphere->color.value == -1)
			set_error(scene, E_INVAL);
		push_sphere_objlist(scene, sphere);
	}
	else if (!sphere || errno != 0)
		set_error(scene, E_MEM);
	free_split(split);
}

void	push_sphere_objlist(t_scene *scene, t_sphere *sphere)
{
	t_object	*obj;
	t_list		*new;

	obj = malloc(sizeof(t_object));
	if (obj)
	{
		obj->u.sp = sphere;
		obj->type = SPHERE;
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
