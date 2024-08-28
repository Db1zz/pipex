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

fclean: clean
	rm -f $(NAME) $(TEST_NAME)

re: fclean all

test: fclean $(PRINTF) 
	@mkdir -p temp_printf_objs
	@cd temp_printf_objs && ar x ../$(PRINTF)
	$(TEST_CC) $(TEST_CFLAGS) $(PRINTF) $(TEST_SRCS) -o $(TEST_NAME)
	@rm -rf temp_printf_objs

.PHONY: all clean fclean re