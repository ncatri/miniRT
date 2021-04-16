#include "../../includes/miniRT.h"

void	parse_ambient_light(char *line, t_scene *scene)
{
	char	**split;
	t_light	amb_light;

	if (scene->ambient.ratio != -1)
	{
		set_error(scene, E_ALREADY_EXISTS);
		return ;
	}
	split = get_split(line, " \t", 3, scene);
	if (split)
	{
		amb_light.ratio = get_ratio(split[1]);
		amb_light.color = get_color(split[2]);
		if (amb_light.ratio == -1 || amb_light.color.value == -1)
			set_error(scene, E_INVAL);
		amb_light.intensity = set_light_intensity(amb_light.color, amb_light.ratio);
		scene->ambient = amb_light;
		free_split(split);
	}
}
