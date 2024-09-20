CC = clang
CFLAGS = -Wall -Wextra -Werror

SRCS = $(addprefix srcs/, \
	main.c \
)
NAME = minishell

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

TEST = srcs/minishell.c

$(NAME): $(SRCS) $(LIBFT)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR) all

.PHONY: all
all: $(NAME)

.PHONY: clean
clean:
	make -C $(LIBFT_DIR) clean

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)

.PHONY: re
re: fclean all

.PHONY: test
test: $(LIBFT)
	$(CC) $(CFLAGS) -g $(TEST) $(LIBFT) -o test
