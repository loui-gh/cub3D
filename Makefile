CC			= gcc 
CFLAGS		= -Wall -Wextra -Werror

NAME		= cub3D
UNAME 		:= $(shell uname)

SRCD		= ./srcs/
SRC			= 	input_utils.c libft_utils.c map_error.c utils.c tex_utils.c ft_split.c \
				main.c draw_utils.c free.c map_init.c textures.c raycast.c \
				movement.c libft_utils_2.c raycast_utils.c movement_utils.c

SRCF		= $(addprefix $(SRCD),$(SRC))
OBJD		= ./objs/

HEADD		= ./incl/
HEADF		= raycast.h

INCL_LINUX	= -lm -Lminilibx-linux -lmlx -lX11 -lXext
INCL_MACOS	= -lm -Lminilibx -lmlx -framework OpenGL -framework AppKit

RM			= rm -f

ifeq ($(UNAME), darwin)
INCL = $(INCL_MACOS)
else
INCL = $(INCL_LINUX)
endif

# for every SRCF file which is an .c file an o file will be created according to the implicit rule (see $(OBJD)%.o: $(SRCD)%.c)
OBJF		= $(SRCF:$(SRCD)%.c=$(OBJD)%.o)
BUILD		= $(OBJF:$(OBJD)%.o)


#if to the respective c file in the source directory no matching o file in the object
#directory is available, then create it according to the following rules:
#Note: the object directory will only be created if not existing already. -p flag throws no errors when already there
#-p is used to prevent the creation of the object directory if it already exists
# add this to Line 41 if on a shitty Mac :)   -I/usr/local/opt/readline/include

all:		${NAME}

$(NAME):	${OBJF}
			$(CC) $(CFLAGS) $(SRCF) ${INCL} -o $(NAME) -L $(HEADD)

$(OBJD)%.o: $(SRCD)%.c
			@mkdir -p $(OBJD)
			$(CC) $(CFLAGS) -I ${HEADD} ${INCL} -c -o $@ $<

clean:
			${RM} ${OBJD}*.o

fclean:		clean
			${RM} ${NAME}

os:
			@echo $(UNAME)

re:			fclean all

.PHONY:		all clean fclean re os