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
		set_cameratoworld_matrix(camera);
		if (camera->position.x == INFINITY || camera->orientation.x == INFINITY || \
camera->fov == -1)
			set_error(scene, E_INVAL);
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
		ft_lstadd_back(&scene->light_list, new);
		if (scene->cur_cam == NULL)
			scene->cur_cam = scene->camera_list;
	}
	else 
		set_error(scene, E_MEM);
}

void	set_cameratoworld_matrix(t_camera *camera)
{
	t_coordinates	cx;
	t_coordinates	cy;
	t_coordinates	cam_up;

	cam_up = set_coordinates(0, 1, 0);
	if (is_equal(camera->orientation, cam_up) || \
			is_equal(camera->orientation, set_coordinates(0, -1, 0)))
		cam_up = set_coordinates(0, 0, 1);
	cx = cross_product(cam_up, camera->orientation);
	cy = cross_product(camera->orientation, cx);
	camera->c2w_matrix[0][0] = cx.x;
	camera->c2w_matrix[0][1] = cx.y;
	camera->c2w_matrix[0][2] = cx.z;
	camera->c2w_matrix[0][3] = 0;
	camera->c2w_matrix[1][0] = cy.x;
	camera->c2w_matrix[1][1] = cy.y;
	camera->c2w_matrix[1][2] = cy.z;
	camera->c2w_matrix[1][3] = 0;
	camera->c2w_matrix[2][0] = camera->orientation.x;
	camera->c2w_matrix[2][1] = camera->orientation.y;
	camera->c2w_matrix[2][2] = camera->orientation.z;
	camera->c2w_matrix[2][3] = 0;
	camera->c2w_matrix[3][0] = camera->position.x;
	camera->c2w_matrix[3][1] = camera->position.y;
	camera->c2w_matrix[3][2] = camera->position.z;
	camera->c2w_matrix[3][3] = 1;
}
