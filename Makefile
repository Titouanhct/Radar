##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## ..
##

NAME	=	my_radar

SRC =   src/main.c
SRC += src/init_towers.c
SRC += src/init_planes.c
SRC += src/quadtree.c
SRC += src/draw.c
SRC += src/handle_collisions.c

OBJ = $(SRC:.c=.o)

CFLAGS = -I./include/ -L lib/ -lmy -Wall -Wextra -g

CFLAGS += -lcsfml-graphics  -lcsfml-window -lcsfml-system -lm

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./lib/
	gcc $(OBJ) -o $(NAME) $(CFLAGS)

clean :
	make clean -C ./lib/
	rm -f $(OBJ)

fclean: clean
	make fclean -C ./lib/
	rm -f $(NAME)

re: fclean all
