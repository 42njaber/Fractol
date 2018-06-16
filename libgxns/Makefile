SRC = draw_fig.c \
	  window.c \
	  display_data.c \
	  images.c \
	  matrix.c \
	  matrix2.c \
	  math.c \
	  vectors.c \
	  colors.c \
	  util.c \
	  gnl/get_next_line.c

ALT_SRC = init_opencl.c

ifndef OPENCL
OPENCL = TRUE
endif

ifeq ($(OPENCL), TRUE)
SRC += init_opencl.c
MACROS += -D OPENCL
endif

NAME = libgxns.a
MLX = ../minilibx_macos/libmlx.a
LFT = ../libft/libft.a
LPF = ../ft_printf/libftprintf.a
FLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

CC = gcc
RM = @rm -fv

DEFAULT	= "\x1b[39m"
RED		= "\x1b[31m"
YELLOW	= "\x1b[32m"
GREEN	= "\x1b[33m"
BLUE	= "\x1b[34m"
MAGENTA	= "\x1b[35m"
CYAN	= "\x1b[36m"
.PHONY: all, clean, force, fclean, re

all: $(NAME)

force:
	@true

$(MLX): force
	@$(MAKE) -C ../minilibx_macos/

$(LFT): force
	@$(MAKE) -C ../libft/

$(LPF): force
	@$(MAKE) -C ../ft_printf/

$(NAME): $(MLX) $(LFT) $(LPF) $(OBJ) ../inc/libgxns.h Makefile
	@rm -f $@
	ar -rc $@ $(OBJ)
	libtool -static -o $@ $@ $(MLX) $(LFT) $(LPF) 2> /dev/null
	ranlib $@

%.o:%.c
	$(CC) $(FLAGS) -o $@ -c $< $(MACROS) -I../inc/

soft_clean:
	@echo "Cleaning library:"
	$(RM) $(NAME)
	@echo "Cleaning objects:"
	$(RM) $(OBJ) $(ALT_SRC:.c=.o)

clean:
	@echo 			"_________________"
	@echo 			"Cleaning objects:"$(RED)
	$(RM) $(OBJ) $(ALT_SRC:.c=.o)
	@echo $(DEFAULT)"_________________"
	$(MAKE) -C ../minilibx_macos/ clean
	$(MAKE) -C ../libft/ fclean
	$(MAKE) -C ../ft_printf/ fclean

fclean: clean
	@echo 			"_________________"
	@echo 			"Cleaning library:"$(RED)
	$(RM) $(NAME)
	@echo $(DEFAULT)"_________________"

re: fclean all

soft_re: soft_clean all
