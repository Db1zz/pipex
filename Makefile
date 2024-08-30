# Project settings
NAME = pipex
CC = cc
# Tiny Note:
# -g flag is used to debug my project, without it debuggers will not
# get the debug information and I will not be able to debug my project.
# After finishing the project, just comment out this flag ;)
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
SRCS =	access.c 	\
		error.c		\
		main.c		\
		parser.c	\
		utils.c		\

OBJS = $(SRCS:.c=.o)
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJS) $(TEST_OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(TEST_NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re