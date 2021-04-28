#include "miniRT.h"

void	prepare_buffer(t_scene *scene)
{
	size_t	img_byte_size;

	img_byte_size = scene->width * scene->height * 3;
	scene->image_buffer = ft_calloc(sizeof(char), img_byte_size);
	if (scene->image_buffer == NULL)
		exit_cleanly_with_message(scene, EXIT_FAIL_BMP, \
				"failed to allocate image buffer");
}

void	color_put_buffer(t_scene scene, int i, int j, t_color color)
{
	unsigned int	pix_i;

	pix_i = (j * scene.width + i) * 3;
	*(scene.image_buffer + pix_i) = (unsigned char)color.b;
	*(scene.image_buffer + pix_i + 1) = (unsigned char)color.g;
	*(scene.image_buffer + pix_i + 2) = (unsigned char)color.r;
}

void	create_bitmap(t_scene scene)
{
	int				n_pad;
	int				i;
	int				i_pad;
	unsigned int	padding[3];

	ft_memset(padding, 0, 3);
	n_pad = (4 - (scene.width * 3) % 4) % 4;
	write_bmpfileheader(&scene, n_pad);
	write_bmpinfoheader(&scene);
	i = -1;
	while (++i < scene.height)
	{
		write(scene.fd, \
				scene.image_buffer + (scene.width * (scene.height - i - 1) * 3), \
				3 * scene.width);
		i_pad = -1;
		while (++i_pad < n_pad)
			write(scene.fd, padding, 1);
	}
}

void	write_bmpfileheader(t_scene *scene, int n_pad)
{
	unsigned char	file_header[BMP_FILEHEADER_SIZE];
	int				filesize;
	int				ret_val;

	filesize = BMP_FILEHEADER_SIZE + BMP_INFOHEADER_SIZE \
			   + (3 * scene->width + n_pad) * scene->height;
	ft_memset(file_header, 0, BMP_FILEHEADER_SIZE);
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	file_header[2] = (unsigned char)(filesize);
	file_header[3] = (unsigned char)(filesize >> 8);
	file_header[4] = (unsigned char)(filesize >> 16);
	file_header[5] = (unsigned char)(filesize >> 24);
	file_header[10] = (unsigned char)(BMP_FILEHEADER_SIZE + \
			BMP_INFOHEADER_SIZE);
	ret_val = write(scene->fd, file_header, BMP_FILEHEADER_SIZE);
	if (ret_val != BMP_FILEHEADER_SIZE)
		exit_cleanly_with_message(scene, EXIT_FAIL_BMP, \
				"failed to write file header");
}

void	write_bmpinfoheader(t_scene *scene)
{
	unsigned char	info_header[BMP_INFOHEADER_SIZE];
	int				ret_val;

	ft_memset(info_header, 0, BMP_INFOHEADER_SIZE);
	info_header[0] = (unsigned char)(BMP_INFOHEADER_SIZE);
	info_header[4] = (unsigned char)(scene->width);
	info_header[5] = (unsigned char)(scene->width >> 8);
	info_header[6] = (unsigned char)(scene->width >> 16);
	info_header[7] = (unsigned char)(scene->width >> 24);
	info_header[8] = (unsigned char)(scene->height);
	info_header[9] = (unsigned char)(scene->height >> 8);
	info_header[10] = (unsigned char)(scene->height >> 16);
	info_header[11] = (unsigned char)(scene->height >> 24);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(8 * 3);
	ret_val = write(scene->fd, info_header, BMP_INFOHEADER_SIZE);
	if (ret_val != BMP_INFOHEADER_SIZE)
		exit_cleanly_with_message(scene, EXIT_FAIL_BMP, \
				"failed to write info header");
}
