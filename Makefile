NAME = asm
CC = gcc
ifeq ($(DEBUG),yes)
	CFLAGS = -Wall -Wextra -g -O0 -fsanitize=address
else
	CFLAGS = -Ofast -march=native -Wall -Wextra
endif

SRC_MAIN = asm.c error.c op.c label.c argument.c instruction.c
SRC_FT = ft_strlen.c ft_isprint.c ft_strchr.c ft_atoi.c ft_strcmp.c ft_isdigit.c
SRC_UTIL = cqueue.c cqueue_ft.c pqueue.c
SRC_IO = openfile.c openfile_write.c
SRC_PARSING = states_main.c states_header.c states_label.c states_instruction.c \
				save_label.c save_argument.c save_instruction.c\
				check_args.c
HEADERS = asm.h op.h ft.h openfile.h states.h cqueue.h pqueue.h

SRC = $(SRC_MAIN) $(SRC_FT) $(SRC_IO) $(SRC_PARSING) $(SRC_UTIL)
OBJ_TMP = $(SRC:.c=.o)

VPATH = src/ft src/io src/main src/parsing src/util
IFLAGS = -Isrc
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(OBJ_TMP))

all : $(NAME) graph

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) -o $@ $< $(IFLAGS)

graph: src/parsing/graph.pdf

src/parsing/graph.pdf: src/parsing/graph.gv
	dot -Tpdf $^ -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re 
