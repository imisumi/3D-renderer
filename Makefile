NAME = renderer

HEADER = includes

CFLAGS = -g -Wall

LFLAGS  = -L/opt/homebrew/Cellar/sdl2/2.26.4/lib -lSDL2 -lm

cc = gcc

OBJ_DIR = .objs
SRC_DIR = ./sources
INC_DIR = ./includes

INC := -I$(INC_DIR)

SRCS =  main.c \
		display.c \
		vector.c \
		mesh.c \
		triangle.c \
		array.c \
		get_next_line.c

OBJS = $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(cc) $(CFLAGS) $(INC) -c -o $@ $<

$(NAME): $(OBJS)
	$(cc) $(CFLAGS) $(INC) $^ $(LFLAGS) -o $(NAME)

run: all
	./renderer

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
