/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 09:43:30 by ncatrien          #+#    #+#             */
/*   Updated: 2021/03/01 17:01:52 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdio.h>
# include "../minilibx/mlx.h"
# include "../libft/libft.h" 

# define NO_ERROR 1
# define ERROR 0

# define TRUE 1
# define FALSE 0

typedef int t_bool;

/* low level abstraction */

typedef struct s_mlx
{
	void	*connection_graphic_server;
	void	*window_id;

	int		checks;	
}				t_mlx;

/* mid level abstraction */

typedef struct s_window
{
	char	*title;
	int		width;
	int		height;
}				t_window;

typedef struct s_image
{
	void	*id;
	char	*address;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}				t_image;

typedef struct s_color
{
	unsigned char	t;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	int				value;
}					t_color;

typedef struct s_coordinates
{
	double	x;
	double	y;
	double	z;
}				t_coordinates;

typedef struct s_sphere
{
	t_coordinates	centre;
	double			diameter;
	t_color			color;
}					t_sphere;

typedef struct s_camera
{
	t_coordinates	position;
	t_coordinates	orientation;
	double			fov;
}				t_camera;

typedef struct s_scene
{
	double		width;
	double		height;
//	t_ambient	lightning;
	t_camera	camera;
	t_sphere	sphere;

	t_bool		valid;
}				t_scene;

typedef struct s_ray
{
	t_coordinates	origin;
	t_coordinates	direction;
}				t_ray;

typedef struct s_polynome2deg
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	sol1;
	double	sol2;
}				t_polynome2deg;

/* mlx management functions */

void		*connection_server(t_mlx *mlx);
void		*connect_window(t_mlx *mlx, t_window window);
t_window	define_window(int width, int height, char *title);
t_mlx		initialize_mlx(t_window window);

/* Window events functions */

void		open_mode(t_window window);
int			keys_find_id(int key, void *param);
void		mode_display_keysid(t_mlx mlx);
int			quit_on_esc(int key, t_mlx *mlx);
int			close_window(int key, t_mlx *mlx);
int			mouse_hook_display_position_and_button(int button, \
		int x, int y, t_mlx *mlx);
int			display_mouse_position_on_click(t_mlx mlx);
int			mouse_angle(int button, int x, int y, t_coordinates *p);
int			mouse_hook_display_angle(t_mlx mlx);
int			mode_quit_on_click_red_cross(t_mlx mlx);
int			close_red_cross(int key, t_mlx *mlx);
void		mode_quit_on_esc(t_mlx mlx);

/* images */

void		pixel_put_image(t_image image, int x, int y, int color);
void		fill_image(t_image image, int color);
t_image		initialize_image(t_mlx mlx, int width, int height);
int			create_trgb(t_color color);
void		draw_rainbow(t_image img);

/* basic operations */

t_coordinates	add(const t_coordinates a, const t_coordinates b);
t_coordinates	substract(const t_coordinates a, const t_coordinates b);
double			dot(t_coordinates a, t_coordinates b);
double			get_norm2(const t_coordinates a);
t_coordinates	normalized(t_coordinates v);

void			ray_tracer(t_image image, t_scene scene);
t_ray			primary_ray(double x, double y, t_scene scene);
t_bool			intersect_sp(t_sphere sp, t_ray ray);

/* parsing */

int				split_len(char **split);
t_scene			initialize_scene(void);
t_scene			scene_extractor(char *filename);
t_bool			check_extension(char *filename);
t_scene			parse_file(int fd);
void			parse_line(char *line, t_scene *scene);
void			parse_resolution(char *line, t_scene *scene);
void			parse_ambient_light(char *line, t_scene *scene);
void			parse_camera(char *line, t_scene *scene);
void			parse_light(char *line, t_scene *scene);
void			parse_sphere(char *line, t_scene *scene);
void			parse_plane(char *line, t_scene *scene);
void			parse_square(char *line, t_scene *scene);
void			parse_cylinder(char *line, t_scene *scene);
void			parse_triangle(char *line, t_scene *scene);

#endif
