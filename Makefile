NAME = asm
CC = gcc
ifeq ($(DEBUG),yes)
	CFLAGS = -Wall -Wextra -g -O0 -fsanitize=address
else
	CFLAGS = -Ofast -march=native -Wall -Wextra
endif

SRC_MAIN = asm.c error.c op.c
SRC_FT = ft_bzero.c ft_strlen.c ft_isprint.c
SRC_IO = openfile.c
SRC_PARSING = ft_line_col.c states_0_4.c states_5_9.c states_10_14.c states_15_19.c
HEADERS = asm.h op.h ft.h openfile.h parsing.h

SRC = $(SRC_MAIN) $(SRC_FT) $(SRC_IO) $(SRC_PARSING)
OBJ_TMP = $(SRC:.c=.o)

VPATH = src/ft src/io src/main src/parsing
IFLAGS = -Isrc
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(OBJ_TMP))

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) -o $@ $< $(IFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re 
