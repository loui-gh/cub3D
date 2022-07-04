SRC =	functions.c 	
OBJ =			$(SRC:.c=.o)
INCLIB = $(INC)/../lib
INC = ./
LFLAGS = -L.. -lmlx -L$(INCLIB) -lXext -lX11 -lm -lz
FLAGS = -Wall -Wextra -Werror
NAME = test
CC = gcc

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LFLAGS) $(FLAGS)

%.o: %.c
	$(CC) -I/usr/local/include -I mlx -O3 -c $< -o $@

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)


re: fclean all

.PHONY: all bonus clean cleanb fclean fcleanb re