CC	= gcc

RM	= rm -f

DIR	= ./src/

NAME	= mysh

SRC	=	$(DIR)alloc.c		\
		$(DIR)builtin.c		\
		$(DIR)epur.c		\
		$(DIR)exec.c		\
		$(DIR)init.c		\
		$(DIR)input.c		\
		$(DIR)is_something.c	\
		$(DIR)main.c		\
		$(DIR)minipipe.c	\
		$(DIR)next_builtins.c	\
		$(DIR)next_cd.c		\
		$(DIR)output.c		\
		$(DIR)parse_cmd.c	\
		$(DIR)path.c		\
		$(DIR)redirect.c	\
		$(DIR)shame.c		\
		$(DIR)signal.c		\
		$(DIR)utilities.c	\
		$(DIR)utils.c

INCLUDE	= -I./include/

CFLAGS	= $(INCLUDE) -W -Wall -Werror -pedantic
LDFLAGS	= -L./lib/ -lmy

OBJ	= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
