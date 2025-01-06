##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## ..
##

NAME	= liblist.a

SRC += create_list.c
SRC += pushback.c
SRC += pushfront.c
SRC += popback.c
SRC += popfront.c
SRC += destroy_node.c
SRC += my_apply_on_matching_nodes.c
SRC += my_apply_on_nodes.c

OBJ = $(SRC:.c=.o)

LDFLAGS = -L./ -llist

CFLAGS =  -I ../include/ -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	ar rc liblist.a $(OBJ)

clean :
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
