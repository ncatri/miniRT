#include "../../includes/miniRT.h"

void	parse_light(char *line, t_scene *scene)
{
	char	**split;
	t_light	*light;

	split = get_split(line, " \t", 4, scene);
	if (split == NULL)
		return ;
	light = malloc(sizeof(t_light));
	if (light)
	{
		light->position = get_coordinates(split[1]);
		light->ratio = get_ratio(split[2]);
		light->color = get_color(split[3]);
		light->intensity = set_light_intensity(light->color, light->ratio);
		if (light->position.x == INFINITY || light->ratio == -1 || \
light->color.value == -1)
			set_error(scene, E_INVAL);
		push_to_lightlist(scene, light);
	}
	else
		set_error(scene, E_MEM);
	free_split(split);
}

t_coordinates	set_light_intensity(t_color color, double ratio)
{
	t_coordinates	rgb;

	rgb.x = color.r / (double)255;
	rgb.y = color.g / (double)255;
	rgb.z = color.b / (double)255;
	return (scalar_mult(ratio, rgb));
}

void	push_to_lightlist(t_scene *scene, t_light *light)
{
	t_list		*new;

	new = ft_lstnew(light);
	if (new)
		ft_lstadd_back(&scene->light_list, new);
	else
		set_error(scene, E_MEM);
}
