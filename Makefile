FILES = main \
		init \
		key_hooks \
		mouse_hooks \
		loop_hook

ALT_FILE = load_opencl \
		   display_opencl \
		   display \
		   colors

CFLAGS = -Llibgxns -lgxns -framework OpenGL -framework AppKit

ifndef KEYBOARD
KEYBOARD = AZERTY
endif

MACROS = -D $(KEYBOARD)

ifndef OPENCL
OPENCL = TRUE
endif

ifeq ($(OPENCL), TRUE)
MACROS += -D OPENCL
FILES += load_opencl display_opencl
CFLAGS += -framework OpenCL
else
FILES += display colors
endif

SRC_DIR = src
SRC = $(FILES:%=$(SRC_DIR)/%.o)

NAME = fractol

OBJ_DIR = obj
OBJ = $(FILES:%=$(OBJ_DIR)/%.o)

LIB = libgxns/libgxns.a
FLAGS = -Wall -Wextra -Werror -Iinc/ 
CC = gcc
RM = @rm -fv
TEST_FILE = test.out
.PHONY: all, test, clean, fclean, re, force

all: $(NAME)

force:
	@true

libgxns/libgxns.a: force
	make -C libgxns/ OPENCL=$(OPENCL) KEYBOARD=$(KEYBOARD)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c inc/fractol.h
	$(CC) $(FLAGS) -o $@ -c $< $(MACROS) 

$(NAME): $(LIB) $(OBJ) Makefile inc/fractol.h
	$(CC) $(CFLAGS) -o $@ $(OBJ)

soft_clean:
	make -C libgxns/ soft_clean
	@echo "Cleaning target:"
	$(RM) $(NAME)
	@echo "Cleaning objects:"
	$(RM) $(OBJ) $(ALT_FILE:%=$(OBJ_DIR)/%.o)

clean:
	@echo "Cleaning objects:"
	$(MAKE) -C libgxns/ fclean
	$(RM) $(OBJ) $(ALT_FILE:%=$(OBJ_DIR)/%.o)

fclean: clean
	@echo "Cleaning target:"
	$(RM) $(NAME)

re: fclean all

soft_re: soft_clean all
