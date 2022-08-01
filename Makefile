CC			= gcc 
CFLAGS		= -Wall -Wextra -Werror -ggdb
INCL		= -I/usr/include -Imlx_linux -O0
#lmlx -- how does that work??
INCL_LINUX	= -lmlx -lXext -lX11 -lm -lz
RM			= rm -f
SRCD		= ./srcs/
SRC			= 	input_utils.c libft_utils.c map_error.c utils.c tex_utils.c ft_split.c \
				main.c draw_utils.c free.c map_init.c textures.c raycast_tex.c \
				movement.c libft_utils_2.c raycast_utils.c movement_utils.c
# Command to add the source folder prefix (instead of having it added manually to SRC)
SRCF		= $(addprefix $(SRCD),$(SRC))
OBJD		= ./objs/
# for every SRCF file which is an .c file an o file will be created according to the implicit rule (see $(OBJD)%.o: $(SRCD)%.c)
OBJF		= $(SRCF:$(SRCD)%.c=$(OBJD)%.o)
BUILD		= $(OBJF:$(OBJD)%.o)


NAME		= cub3D
HEADD		= ./incl/
HEADF		= raycast.h

# LIBFTDIR	= ./libs/libft/
# LIBFT_OBJD	= objs
# LIBFT_SRCD	= srcs/
# LIBFTL		= libft.a

# LIBFT_OBJF    = ${LIBFTDIR}/*.o
#LIBFT_MAKE    = make -C ${LIBFTDIR}

#if to the respective c file in the source directory no matching o file in the object
#directory is available, then create it according to the following rules:
#Note: the object directory will only be created if not existing already. -p flag throws no errors when already there
#-p is used to prevent the creation of the object directory if it already exists
# add this to Line 41 if on a shitty Mac :)   -I/usr/local/opt/readline/include
$(OBJD)%.o: $(SRCD)%.c
	@mkdir -p $(OBJD)
	$(CC) $(CFLAGS) -I ${HEADD} ${INCL} ${INCL_LINUX} -c -o $@ $< 

# $(NAME):	${OBJF}
# 			make libftmake
# 			$(CC) $(CFLAGS) $(SRCF) -o $(NAME) $(HEADD)$(HEADF) $(LIBFTD)$(LIBFTL)
# add this lib if you are on a Mac :) -L/usr/local/opt/readline/lib
$(NAME):	${OBJF}
			$(CC) $(CFLAGS) $(SRCF) ${INCL} ${INCL_LINUX} -o $(NAME) -L $(HEADD) 


all:		${NAME}

clean:
			${RM} ${OBJD}*.o

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re