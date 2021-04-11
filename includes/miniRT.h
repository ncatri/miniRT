/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 09:43:30 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/11 15:21:13 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdio.h>
# include <errno.h>
# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include "codes.h"

# define TRUE (1)
# define FALSE (0)

# define WINDOW_TITLE "The dankest miniRT"
# define SHININESS (10)
# define ACNEA (0.01)

typedef int t_bool;

enum e_obj {SPHERE, PLANE, SQUARE, TRIANGLE, CYLINDER};

typedef struct s_mlx
{
	void	*connection_graphic_server;
	void	*window_id;
	int		width;
	int		height;
	char	*title;

	int		checks;	
}				t_mlx;

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
	int	t;
	int	r;
	int	g;
	int	b;
	int	value;
}					t_color;

typedef struct s_coordinates
{
	double	x;
	double	y;
	double	z;
}				t_coordinates;

typedef struct s_plane
{
	t_coordinates	position;
	t_coordinates	orientation;
	t_color			color;
}				t_plane;

typedef struct s_sphere
{
	t_coordinates	centre;
	double			diameter;
	t_color			color;
}					t_sphere;

typedef struct	s_square
{
	t_coordinates	position;
	t_coordinates	orientation;
	t_coordinates	up;
	t_coordinates	right;
	double			side;
	t_color			color;
	double			coord_matrix[4][4];
}				t_square;

typedef	struct	s_triangle
{
	t_coordinates	p1;
	t_coordinates	p2;
	t_coordinates	p3;
	t_coordinates	v12;
	t_coordinates	v23;
	t_coordinates	v31;
	t_coordinates	normal;
	t_color			color;
}				t_triangle;

typedef	struct	s_cylinder
{
	t_coordinates	position;
	t_coordinates	orientation;
	double			diameter;
	double			height;
	t_color			color;
}				t_cylinder;

typedef struct s_camera
{
	t_coordinates	position;
	t_coordinates	orientation;
	double			fov;
	double			c2w_matrix[4][4];
}				t_camera;

typedef struct s_light
{
	t_coordinates	position;
	t_color			color;
	double			ratio;
	t_coordinates	intensity;
}				t_light;

union u_objects
{
	t_sphere	*sp;
	t_plane		*pl;
	t_square	*sq;
	t_triangle	*tr;
	t_cylinder	*cy;
};	

typedef struct s_object
{
	int				type;
	union u_objects	u;
}				t_object;

typedef struct s_scene
{
	t_mlx		mlx;

	int			width;
	int			height;
	double		ratio;

	t_light		ambient;
	t_list		*camera_list;
	t_list		*cur_cam;
	t_list		*light_list;
	t_list		*cur_light;
	t_list		*objects_list;

	t_bool		valid;
	char		*err_msg;
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

typedef struct	s_intersection
{
	double		min_dist;
	t_coordinates	p_hit;
	t_coordinates	norm_hit;
	t_object	*obj;
	t_color		color;
}				t_intersection;

/* mlx management functions */

void		set_mlx(t_scene *scene);
int			key_hooks(int key, t_scene *scene);
int			red_cross_quit(int key, t_scene *scene);

void		display_something(t_scene scene);

/* images */

void		pixel_put_image(t_image image, int x, int y, t_color color);
void		fill_image(t_image image, t_color color);
t_image		initialize_image(t_mlx mlx, int width, int height);
int			create_trgb(t_color color);
t_color		set_color(int r, int g, int b);
void		draw_rainbow(t_image img);

/* mathematics */

t_coordinates	add(const t_coordinates a, const t_coordinates b);
t_coordinates	substract(const t_coordinates a, const t_coordinates b);
double			dot(t_coordinates a, t_coordinates b);
double			get_norm2(const t_coordinates a);
t_coordinates	normalized(t_coordinates v);

t_coordinates	cross_product(t_coordinates a, t_coordinates b);
void			print_matrix44d(double matrix[4][4]);
t_coordinates	set_coordinates(double a, double b, double c);
t_bool			is_equal(t_coordinates a, t_coordinates b);
void			set_cameratoworld_matrix(t_camera *camera);
t_coordinates	mult_vec_matrix(double mat[4][4], t_coordinates vec);
t_coordinates	scalar_mult(double k, t_coordinates vect);

void			ray_tracer(t_image image, t_scene scene);
t_ray			primary_ray(int x, int y, t_scene scene);
double			intersect_sp(t_sphere *sp, t_ray ray);
double			intersect_pl(t_plane *pl, t_ray ray);
t_coordinates	get_plane_normal(t_plane *plane, t_ray ray);
double			intersect_sq(t_square *sq, t_ray ray);
t_coordinates	get_square_normal(t_square *square, t_ray ray);
double			intersect_tr(t_triangle *tr, t_ray ray);
t_bool			is_hit_inside_triangle(t_coordinates point, t_triangle *tr);
t_coordinates	get_triangle_normal(t_triangle *triangle, t_ray ray);
double			intersect_cy(t_cylinder *cy, t_ray ray);
double			coef_a(t_cylinder cy, t_ray ray);
double			coef_b(t_cylinder cy, t_ray ray);
double			coef_c(t_cylinder cy, t_ray ray);

t_intersection	init_intersection(void);
t_bool			found_intersection(t_ray prim_ray, t_scene scene, \
		t_intersection *inter);
void			set_intersection(t_ray prim_ray, t_scene scene, \
		t_intersection *inter);
double			get_obj_intersect(t_object *obj, t_ray ray);
t_color			get_obj_color(t_object *obj);
t_coordinates	get_normal(t_intersection *inter, t_ray ray);

int				iter_cur_cam(t_scene *scene);

/* shading */

void			compute_shading(t_scene scene, t_ray prim_ray, t_intersection *inter);
t_color			mult_color(t_color color, t_coordinates mult);
t_bool			get_light(t_scene scene, t_intersection *inter, t_ray light_ray);
t_bool			iterate_current_light(t_scene *scene);
t_ray			cast_light_ray(t_light *light, t_intersection *inter);
t_coordinates	set_light_intensity(t_color color, double ratio);
t_color			add_diffuse(t_intersection *inter, t_ray light_ray, t_light *light);
t_color			add_specular(t_intersection *inter, t_ray light_ray, \
		t_light *light, t_ray prim_ray);

t_color			add_colors(t_color color1, t_color color2);

/* parsing */

t_bool			check_complete(t_scene *scene);
void			set_error(t_scene *scene, char *message);
void			free_all(t_scene *scene);
void			free_obj(void *content);
char			**get_split(char *line, char *sep, int size, t_scene *scene);
t_bool			check_args(int argc, char **argv);
double			get_positive_val(char *str);
double			get_fov(char *str);
double			get_ratio(char *str);
t_coordinates	get_coordinates(char *data);
t_color			get_color(char *data);
t_bool			valid_rgb(t_color color);
t_bool			str_isnumber(const char *str);
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
void			set_sphere_object(t_scene *scene, t_sphere *sphere);
void			parse_plane(char *line, t_scene *scene);
void			set_plane_object(t_scene *scene, t_plane *plane);
void			parse_square(char *line, t_scene *scene);
void			set_square_object(t_scene *scene, t_square *square);
void			set_orientation_vectors(t_square *sq);
void			parse_cylinder(char *line, t_scene *scene);
void			push_cylinder_objlist(t_scene *scene, t_cylinder *cy);
void			parse_triangle(char *line, t_scene *scene);
void			set_triangle_vectors(t_triangle *triangle);
void			push_triangle_objlist(t_scene *scene, t_triangle *triangle);

/* debug */

void			print_objlist(t_scene scene);
void			print_coord(t_coordinates coord);
void			print_color(t_color col);
void			print_sphere(t_sphere sp);
void			print_plane(t_plane pl);
void			print_square(t_square sq);
void			print_camera(t_camera *cam);
void			print_triangle(t_triangle tr);
void			print_cylinder(t_cylinder cy);

#endif
