CC			= gcc 
CFLAGS		= -Wall -Wextra -Werror -ggdb

NAME		= cub3D
UNAME 		:= $(shell uname)

SRCD		= ./srcs/
SRC			= 	close_window.c libft_utils.c map_error.c utils.c tex_utils.c ft_split.c \
				main.c draw_floor_ceiling.c free.c map_init.c textures.c raycast.c \
				movement.c libft_utils_2.c raycast_utils.c rotation.c

SRCF		= $(addprefix $(SRCD),$(SRC))
OBJD		= ./objs/

HEADD		= ./incl/
HEADF		= raycast.h

INCL_LINUX	= -lm -Lminilibx-linux -lmlx -lX11 -lXext -ggdb
INCL_MACOS	= -lm -Lminilibx -lmlx -framework OpenGL -framework AppKit

MLX_LINUX	= mlx_linux
MLX_MACOS	= minilibx

RM			= rm -f

ifeq ($(UNAME), Darwin)
INCL = $(INCL_MACOS)
MLX	 = $(MLX_MACOS)
else
INCL = $(INCL_LINUX)
MLX	 = $(MLX_LINUX)
endif

# for every SRCF file which is an .c file an o file will be created according to the implicit rule (see $(OBJD)%.o: $(SRCD)%.c)
OBJF		= $(SRCF:$(SRCD)%.c=$(OBJD)%.o)
BUILD		= $(OBJF:$(OBJD)%.o)


all:		mlx ${NAME}

$(NAME):	${OBJF}
			$(CC) $(CFLAGS) $(SRCF) ${INCL} -o $(NAME) -L $(HEADD)

$(OBJD)%.o: $(SRCD)%.c
			@mkdir -p $(OBJD)
			$(CC) $(CFLAGS) -I ${HEADD} -c -o $@ $<

mlx:		
			$(MAKE) -C $(MLX)

clean:
			${RM} ${OBJF}

cleanminilib:
			$(MAKE) -C $(MLX) clean

fclean:		clean
			${RM} ${NAME}

fcleanall: 	fclean cleanminilib
			${RM} ${MLX}/libmlx.a
os:
			@echo $(UNAME)

re:			fclean all

reall: 		fcleanall all

.PHONY:		all clean fclean re os 