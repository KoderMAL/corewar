NAME = asm
CC = gcc
ifeq ($(DEBUG),yes)
	CFLAGS = -Wall -Wextra -g -O0
else
	CFLAGS = -Ofast -march=native -Wall -Wextra
endif

SRC_MAIN = asm.c error.c op.c label.c argument.c instruction.c make_cor.c
SRC_FT = ft_strlen.c ft_isprint.c ft_strchr.c ft_atoi.c ft_strcmp.c ft_isdigit.c\
		 ft_strcpy.c ft_memset.c
SRC_UTIL = cqueue.c cqueue_ft.c pqueue.c
SRC_IO = openfile.c openfile_write.c
SRC_HASH = crc32_init_0.c crc32_init_1.c crc32_init_2.c crc32_init.c crc32.c
SRC_PARSING = states_main.c states_header.c states_label.c states_instruction.c \
			  save_label.c save_argument.c save_instruction.c check_args.c
SRC_TESTS = $(SRC_IO) $(SRC_FT) $(SRC_UTIL) \
			tests.c tests_assert.c \
			ft_atoi_test.c ft_strchr_test.c ft_test.c \
			pqueue_test.c cqueue_test.c cqueue_test_2.c \
			tests_main.c
SRC_ASSEMBLY = assemble.c first_pass.c second_pass.c store_locations.c \
			   assemble_op.c encode_bytes.c
HEADERS = asm.h op.h ft.h openfile.h states.h cqueue.h pqueue.h crc32.h assembly.h

SRC = $(SRC_MAIN) $(SRC_FT) $(SRC_IO) $(SRC_PARSING) $(SRC_UTIL) $(SRC_HASH) $(SRC_ASSEMBLY)
OBJ_TMP = $(SRC:.c=.o)
SRC2 = $(SRC_VM) $(SRC_IO) $(SRC_FT) $(SRC_UTIL)
OBJ2_TMP = $(SRC2:.c=.o)

VPATH = src/ft src/io src/main src/parsing src/util src/hash src/tests src/assembly src/VM
IFLAGS = -Isrc
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(OBJ_TMP))
OBJ2 = $(addprefix $(OBJ_DIR)/, $(OBJ2_TMP))

OBJ_TMP_TESTS = $(SRC_TESTS:.c=.o)
	OBJ_TESTS = $(addprefix $(OBJ_DIR)/, $(OBJ_TMP_TESTS))

all : $(NAME) graph

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(NAME2): $(OBJ2)
	$(CC) $(CFLAGS) -o $(NAME2) $(OBJ2)

$(OBJ_DIR)/%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) -o $@ $< $(IFLAGS)

graph: src/parsing/graph.pdf

src/parsing/graph.pdf: src/parsing/graph.gv
	dot -Tpdf $^ -o $@

test: $(OBJ_TESTS)
	$(CC) $(CFLAGS) -o test $(OBJ_TESTS)
	./test

clean:
	rm -f $(OBJ) $(OBJ_TESTS)

fclean: clean
	rm -f $(NAME) $(NAME2) test

re: fclean all

.PHONY: all, clean, fclean, re, test
