#include "../includes/miniRT.h"

void	prepare_output_file(t_scene *scene, char *scene_path)
{
	int		fd;
	char	*outfile_name;

	(void)scene;
	outfile_name = extract_filename(scene_path);
	if (outfile_name == NULL)
	{
		free(outfile_name);
		exit_cleanly_with_message(scene, EXIT_FAIL_BMP, \
				"failed to extract output file name");
	}
	fd = open(outfile_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	free(outfile_name);
	if (fd < 0)
		exit_cleanly_with_message(scene, EXIT_FAIL_BMP, \
				"failed to create output file");
	scene->fd = fd;
}

char	*extract_filename(char *scene_path)
{
	char	*filename;
	char	*rootname;

	filename = get_filename(scene_path);
	rootname = replace_suffix(filename);
	free(filename);
	return (rootname);
}

char	*get_filename(char *scene_path)
{
	char	**tmp_split;
	char	*tmp;

	tmp_split = ft_split(scene_path, "/");
	if (tmp_split)
	{
		tmp = ft_strdup(tmp_split[split_len(tmp_split) - 1]);
		free_split(tmp_split);
		return (tmp);
	}
	return (NULL);
}

char	*replace_suffix(char *filename)
{
	char	**tmp_split;
	char	*root;
	char	*result;

	if (filename == NULL)
		return (NULL);
	tmp_split = ft_split(filename, ".");
	if (tmp_split == NULL)
		return (NULL);
	root = ft_strdup(tmp_split[0]);
	free_split(tmp_split);
	result = ft_strjoin(root, ".bmp");
	free(root);
	return (result);
}

void	prepare_buffer(t_scene *scene)
{
	scene->image_buffer = ft_calloc(sizeof(char), scene->width * scene->height * 3);
	if (scene->image_buffer == NULL)
		exit_cleanly_with_message(scene, EXIT_FAIL_BMP, \
				"failed to allocate image buffer");
}

void	color_put_buffer(t_scene scene, int i, int j, t_color color)
{
	unsigned int	pix_i;

	pix_i = (j * scene.width + i) * 3;
//	*(scene.image_buffer + j * 3 * scene.width + i * 3) = (unsigned char)color.r;
	*(scene.image_buffer + pix_i) = (unsigned char)color.b;
	*(scene.image_buffer + pix_i + 1) = (unsigned char)color.g;
	*(scene.image_buffer + pix_i + 2) = (unsigned char)color.r;

}

void	create_bitmap(t_scene scene)
{
	unsigned char	file_header[14] = {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0};
	unsigned char	info_header[40] = {40, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0};
	unsigned char	padding[3] = {0, 0, 0};
	int				filesize;

	filesize = 54 + 3 * scene.width * scene.height;

	file_header[2] = (unsigned char)(filesize);
	file_header[3] = (unsigned char)(filesize >> 8);
	file_header[4] = (unsigned char)(filesize >> 16);
	file_header[5] = (unsigned char)(filesize >> 24);

	info_header[4] = (unsigned char)(scene.width);
	info_header[5] = (unsigned char)(scene.width >> 8);
	info_header[6] = (unsigned char)(scene.width >> 16);
	info_header[7] = (unsigned char)(scene.width >> 24);
	info_header[8] = (unsigned char)(scene.height);
	info_header[9] = (unsigned char)(scene.height >> 8);
	info_header[10] = (unsigned char)(scene.height >> 16);
	info_header[11] = (unsigned char)(scene.height >> 24);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(8 * 3);
	
	write(scene.fd, file_header, 14);
	write(scene.fd, info_header, 40);
	
	int	i;
	int	n_pad;
	int	i_pad;

	n_pad = (4 - (scene.width * 3) % 4) % 4;
	i = 0;
	while (i < scene.height)
	{
		write(scene.fd, scene.image_buffer + (scene.width*(scene.height - i -1)*3),3*scene.width);
		i_pad = 0;
		while (i_pad < n_pad)
		{
			write(scene.fd, padding, 3);
			i_pad++;
		}
		i++;
	}
}
