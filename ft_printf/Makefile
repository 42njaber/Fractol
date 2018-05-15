SRC = ft_mapper.c \
	  ft_printf.c \
	  ft_pf_chr.c \
	  ft_pf_dbl.c \
	  ft_pf_int.c \
	  ft_pf_len.c \
	  ft_pf_str.c \
	  pf_buf.c \
	  pf_format.c \
	  pf_utility.c

NAME = libftprintf.a
FLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

LIB = ../libft/libft.a
CC = gcc
RM = @rm -fv
.PHONY: all, test, clean, fclean, re, force

all: $(NAME)

force:
	@true

%.o: %.c ft_printf.h
	$(CC) $(FLAGS) -c $< -I ../inc

$(NAME): $(LIB) $(OBJ) ft_printf.h Makefile
	rm -fv $(NAME)
	ar -rc $(NAME) $(OBJ)

clean:
	@echo "Cleaning objects:"
	$(RM) $(OBJ)

fclean: clean
	@echo "Cleaning library:"
	$(RM) $(NAME)
	$(RM) $(TEST_FILE)

re: fclean all
