#include "../../includes/miniRT.h"

void	parse_camera(char *line, t_scene *scene)
{
	char		**split;
	t_camera	*camera;

	split = get_split(line, " \t", 4, scene);
	if (split == NULL)
		return ;
	camera = malloc(sizeof(t_camera));
	if (camera)
	{
		camera->position = get_coordinates(split[1]);
		camera->orientation = get_coordinates(split[2]);
		camera->fov = get_fov(split[3]);
		if (camera->position.x == INFINITY || camera->orientation.x == INFINITY || \
camera->fov == -1)
			set_error(scene, E_INVAL);
		else if (fabs(get_norm2(camera->orientation) - 1) > PRECISION)
			set_error(scene, E_NOT_NORMED);
		push_to_camlist(scene, camera);
	}
	else
		set_error(scene, E_MEM);
	free_split(split);
}

void	push_to_camlist(t_scene *scene, t_camera *camera)
{
	t_list		*new;

	new = ft_lstnew(camera);
	if (new)
	{
		ft_lstadd_back(&scene->camera_list, new);
		if (scene->cur_cam == NULL)
			scene->cur_cam = scene->camera_list;
	}
	else
		set_error(scene, E_MEM);
}
