FOLDER = srcs/

SRCS_LIST =	graphic_interface/window.c \
			graphic_interface/keys.c \
			graphic_interface/mouse.c \
			graphic_interface/images.c \
			math/basic_operations.c \
			math/sphere.c \
			geometry/draw.c \
			parsing/parser.c

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

$(NAME): $(OBJS) main.c
	$(MAKE) -C $(MLX)
	mv $(MLX)/libmlx.dylib .
	$(MAKE) -C $(LIBFT)
	mv $(LIBFT)/$(LIBFT).a .
	$(CC) $(CFLAGS) $(LIBFLAGS) $(MLXFLAGS) -g $(OBJS) main.c -o $(NAME)

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
