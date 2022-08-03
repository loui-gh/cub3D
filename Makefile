CC			= gcc 
CFLAGS		= -Wall -Wextra -Werror

NAME		= cub3D
UNAME 		:= $(shell uname)

SRCD		= ./srcs/
SRC			= 	input_utils.c libft_utils.c map_error.c utils.c tex_utils.c ft_split.c \
				main.c draw_utils.c free.c map_init.c textures.c raycast.c more_utils.c \
				movement.c libft_utils_2.c raycast_utils.c movement_utils.c

SRCF		= $(addprefix $(SRCD),$(SRC))
OBJD		= ./objs/

HEADD		= ./incl/
HEADF		= raycast.h

INCL_LINUX	= -lm -Lminilibx-linux -lmlx -lX11 -lXext
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
			$(MAKE) -C $(MLX) clean
			${RM} ${OBJF}

fclean:		clean
			${RM} ${MLX}/libmlx.a
			${RM} ${NAME}

os:
			@echo $(UNAME)

re:			fclean all

.PHONY:		all clean fclean re os