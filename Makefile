FOLDER = srcs/

SRCS_LIST =	graphic_interface/window.c \
			graphic_interface/images.c \
			intersections/operations1.c \
			intersections/operations2.c \
			intersections/sphere.c \
			intersections/plane.c \
			intersections/square.c \
			intersections/triangle.c \
			intersections/cylinder.c \
			intersections/cylinder2.c \
			renderer/draw.c \
			renderer/colors.c \
			renderer/get_objects.c \
			renderer/scene_utils.c \
			renderer/shading.c \
			parsing/parser.c \
			parsing/parse_resolution.c \
			parsing/parse_ambient_light.c \
			parsing/parse_camera.c \
			parsing/parse_light.c \
			parsing/parse_sphere.c \
			parsing/parse_plane.c \
			parsing/parse_square.c \
			parsing/parse_triangle.c \
			parsing/parse_cylinder.c \
			parsing/parse_utils.c \
			parsing/parse_errors.c \
			parsing/data_extractors.c \
			parsing/data_extractors2.c \
			bitmap/bitmap.c \
			bitmap/create_file.c \
			debug/debug.c \
			debug/debug2.c \
			debug/debug3.c \

SRCS = $(addprefix $(FOLDER), $(SRCS_LIST))

NAME = miniRT

OBJS = $(SRCS:.c=.o)

HEADER = ~/$(NAME)/includes/

RM = rm -f

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LIBFLAGS = -L . -lft

MLXFLAGS = -L $(MLX) -lmlx -framework OpenGL -framework AppKit

MLX = minilibx
LIBFT = libft

%.o: %.c
	$(CC) $(CFLAGS) -g -I $(HEADER) -c $< -o $@

all: $(NAME)

$(NAME): $(LIBFT).a libmlx.dylib $(OBJS) main.c 
	$(CC) $(CFLAGS) $(LIBFLAGS) $(MLXFLAGS) -I $(HEADER) -g $(OBJS) main.c -o $(NAME)

$(LIBFT).a:
	$(MAKE) -C $(LIBFT)
	mv $(LIBFT)/$(LIBFT).a .
	cp -R $(LIBFT)/includes/ $(HEADER)

libmlx.dylib:
	$(MAKE) -C $(MLX)
	mv $(MLX)/libmlx.dylib .
	cp $(MLX)/mlx.h $(HEADER)

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(LIBFT)
	$(MAKE) clean -C $(MLX)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT)
	$(RM) libmlx.dylib
	$(RM) libft.a
	$(RM) $(HEADER)get_next_line.h
	$(RM) $(HEADER)libft.h
	$(RM) $(HEADER)mlx.h
	$(RM) -rf $(NAME).dSYM

re: fclean all

.PHONY: clean fclean re all
