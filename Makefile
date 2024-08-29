# Project settings
NAME = pipex
CC = cc
# Tiny Note:
# -g flag is used to debug my project, without it debuggers will not
# get the debug information and I will not be able to debug my project.
# After finishing the project, just comment out this flag ;)
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
SRCS =  $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
PRINTF_DIR = ./ft_printf
PRINTF = $(PRINTF_DIR)/libftprintf.a

all: $(PRINTF) $(NAME)

$(PRINTF):
	$(MAKE) -C $(PRINTF_DIR)

$(NAME): $(SRCS)
	@mkdir -p temp_printf_objs
	@cd temp_printf_objs && ar x ../$(PRINTF)
	$(CC) $(CFLAGS) $(SRCS) $(PRINTF) -o $(NAME)
	@rm -rf temp_printf_objs

clean:
	rm -f $(OBJS) $(TEST_OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(PRINTF_DIR) clean

fclean: clean
	rm -f $(NAME) $(TEST_NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re