#include "miniRT.h"

void	print_sphere(t_sphere sp)
{
	printf("\tposition --> ");
	print_coord(sp.centre);
	printf("\tdiameter --> %.2f\n", sp.diameter);
	printf("\tcolor --> ");
	print_color(sp.color);
}

void	print_plane(t_plane pl)
{
	printf("\tposition --> ");
	print_coord(pl.position);
	printf("\torientation --> ");
	print_coord(pl.orientation);
	printf("\tcolor --> ");
	print_color(pl.color);
}

void	print_camera(t_camera *cam)
{
	printf("----camera----\n");
	printf("\tposition --> ");
	print_coord(cam->position);
	printf("\torientation --> ");
	print_coord(cam->orientation);
	printf("\tfov --> ");
	printf("%.1f\n", cam->fov);
	print_matrix44d(cam->c2w_matrix);
	printf("----\n");
}

void	print_square(t_square sq)
{
	printf("\tposition --> ");
	print_coord(sq.position);
	printf("\torientation --> ");
	print_coord(sq.orientation);
	printf("\tright --> ");
	print_coord(sq.right);
	printf("\tup --> ");
	print_coord(sq.up);
	printf("\tside length --> %.2f\n", sq.side);
	printf("\tcolor --> ");
	print_color(sq.color);
}

void	print_triangle(t_triangle tr)
{
	printf("\tp1 --> ");
	print_coord(tr.p1);
	printf("\tp2 --> ");
	print_coord(tr.p2);
	printf("\tp3 --> ");
	print_coord(tr.p3);
	printf("\tcolor --> ");
	print_color(tr.color);
	printf("\tv12 --> ");
	print_coord(tr.v12);
	printf("\tv23 --> ");
	print_coord(tr.v23);
	printf("\tv31 --> ");
	print_coord(tr.v31);
	printf("\tnormal --> ");
	print_coord(tr.normal);
}
