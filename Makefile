FOLDER = srcs/

SRCS_LIST =	graphic_interface/window.c \
			graphic_interface/images.c \
			math/operations1.c \
			math/operations2.c \
			math/sphere.c \
			math/plane.c \
			math/square.c \
			math/triangle.c \
			math/cylinder.c \
			math/cylinder2.c \
			geometry/draw.c \
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
			debug.c \
			shading.c \
			colors.c \
			scene_utils.c

SRCS = $(addprefix $(FOLDER), $(SRCS_LIST))

OBJS = $(SRCS:.c=.o)

HEADER = includes/

RM = rm -f

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LIBFLAGS = -L . -lft

MLXFLAGS = -L $(MLX) -lmlx -framework OpenGL -framework AppKit

NAME = miniRT

MLX = minilibx
LIBFT = libft

%.o: %.c
	$(CC) $(CFLAGS) -g -I $(HEADER) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) main.c $(LIBFT).a libmlx.dylib
	$(CC) $(CFLAGS) $(LIBFLAGS) $(MLXFLAGS) -g $(OBJS) main.c -o $(NAME)

hometest: $(OBJS) home.c $(LIBFT).a
	$(CC) $(CFLAGS) -g $(OBJS) home.c $(LIBFLAGS) -lm -o home$(NAME)

$(LIBFT).a:
	$(MAKE) -C $(LIBFT)
	mv $(LIBFT)/$(LIBFT).a .

libmlx.dylib:
	$(MAKE) -C $(MLX)
	mv $(MLX)/libmlx.dylib .

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(LIBFT)
	$(MAKE) clean -C $(MLX)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT)
	$(RM) libmlx.dylib
	$(RM) libft.a
	$(RM) -r $(NAME).dSYM

re: fclean all

.PHONY: clean fclean re
