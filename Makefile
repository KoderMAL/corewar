NAME = asm

SRC = asm.c\
	  openfile.c\
	  error.c\
	  states_0-4.c\
	  states_5-9.c\
	  ft_strlen.c\
	  ft_bzero.c\

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror
CC = gcc $(FLAGS)

all : $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $@
	@echo "\033[32m> [asm] ready to use.\033[00m"
	@echo "usage: ./asm [file.s]"

%.o: %.c
	@$(CC) -o $@ -c $<

clean:
	@rm -f $(OBJ)
	@echo "Objects cleaned"

fclean: clean
	@rm -f $(NAME)
	@echo "asm cleaned"

re: fclean all

.PHONY: all, clean, fclean, re 
