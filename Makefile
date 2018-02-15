NAME = asm
NAME2 = corewar
CC = gcc

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	MLX = lib/minilibx_linux
	LDFLAGS = -L $(MLX) -lmlx -L/usr/include/../lib -lXext -lX11 -lm -lbsd 
	ifeq ($(DEBUG),yes)
		CFLAGS = -Wall -Wextra -std=c99 -g -O0 -I./$(MLX) -DLINUX
	else
		CFLAGS = -Ofast -march=native -fomit-frame-pointer -Wall -Wextra -std=c99 -I./$(MLX) -DLINUX
	endif
endif
ifeq ($(UNAME_S),Darwin)
	MLX = lib/minilibx_elcapitan
	LDFLAGS = -framework openGL -framework AppKit $(MLX)/libmlx.a
	ifeq ($(DEBUG),yes)
		CFLAGS = -Wall -Wextra -std=c99 -g -O0 -I./$(MLX) -fsanitize=address
	else
		CFLAGS = -Ofast -fomit-frame-pointer -Wall -Wextra -std=c99 -I./$(MLX)
	endif
endif

SRC_ASM = asm.c parse.c error.c op.c label.c argument.c instruction.c make_cor.c \
			assemble.c pass.c store_locations.c assemble_op.c encode_bytes.c
SRC_FT = ft_strlen.c ft_isprint.c ft_strchr.c ft_atoi.c ft_strcmp.c ft_isdigit.c \
		 ft_strcpy.c ft_memset.c ft_isspace.c ft_memcpy.c
SRC_UTIL = cqueue.c cqueue_ft.c pqueue.c pqueue_util.c
SRC_IO = openfile.c openfile_write.c openfile_read.c
SRC_PARSING = states_main.c states_header.c states_label.c states_instruction.c \
			  save_label.c save_argument.c save_instruction.c check_args.c
SRC_COREWAR = parse_args.c error2.c thread.c vm.c champion.c draw_game.c dump.c cycle.c op.c \
				live.c zjmp.c fork.c aff.c ld.c params.c add.c sub.c and.c \
				lfork.c lld.c ldi.c ldi_dir.c ldi_reg.c \
				lldi.c lldi_dir.c lldi_reg.c sti.c sti_ind.c sti_reg.c \
				st.c xor.c or.c \
				and_or_xor_one.c and_or_xor_two.c \
				op_success.c op_exit.c \
				check_cycles.c verbose.c
SRC_GUI = font.c font_cursor.c gui.c gui_hooks.c fonts.c
SRC_TESTS = $(SRC_IO) $(SRC_FT) $(SRC_UTIL) \
			tests.c tests_assert.c \
			ft_atoi_test.c ft_strchr_test.c ft_test.c \
			pqueue_test.c cqueue_test.c cqueue_test_2.c \
			tests_main.c
HEADERS = vm.h asm.h op.h ft.h openfile.h states.h cqueue.h pqueue.h assembly.h \
			font.h gui.h gui_corewar.h

SRC = $(SRC_FT) $(SRC_IO) $(SRC_PARSING) $(SRC_UTIL) $(SRC_ASM)
OBJ_TMP = $(SRC:.c=.o)
SRC2 = $(SRC_FT) $(SRC_IO) $(SRC_UTIL) $(SRC_GUI) $(SRC_COREWAR)
OBJ2_TMP = $(SRC2:.c=.o)

VPATH = src/ft src/io src/asm src/parsing src/util src/tests src/corewar src/gui
IFLAGS = -Isrc
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(OBJ_TMP))
OBJ2 = $(addprefix $(OBJ_DIR)/, $(OBJ2_TMP))

OBJ_TMP_TESTS = $(SRC_TESTS:.c=.o)
OBJ_TESTS = $(addprefix $(OBJ_DIR)/, $(OBJ_TMP_TESTS))

all : $(NAME) $(NAME2) graph

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(NAME2): $(OBJ2)
	make -C $(MLX)/ all
	$(CC) $(CFLAGS) -o $(NAME2) $(OBJ2) $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) -o $@ $< $(IFLAGS)

graph: src/parsing/graph.pdf

src/parsing/graph.pdf: src/parsing/graph.gv
	dot -Tpdf $^ -o $@

test: $(OBJ_TESTS)
	$(CC) $(CFLAGS) -o test $(OBJ_TESTS)
	./test

clean:
	make -C $(MLX)/ clean
	rm -f $(OBJ) $(OBJ2) $(OBJ_TESTS)

fclean: clean
	rm -f $(NAME) $(NAME2) test

re: fclean all

.PHONY: all, clean, fclean, re, test
