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
