include common.mk
include library.mk

NAME := minishell
SRCS := $(addprefix $(SRCS_DIR)/, \
	minishell.c \
)
OBJS := $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))
INCLUDES := $(addprefix $(INCLUDES_DIR)/, \
	$(addprefix $(NAME)/, \
		minishell.h \
	) \
)
INCFLAGS := $(addprefix -I, \
	/usr/include \
	$(INCLUDES_DIR) \
	$(LIBFT_DIR)/$(INCLUDES_DIR) \
)
LIBS := $(LIBFT)
LIBFLAGS := -lreadline

NUM_FILES := $(words $(SRCS))

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(INCLUDES)
	@mkdir -p $(@D)
	@printf \
		"\r$(CLEAR)%-15s: [%2d/%2d] $(GREEN)compiling $(CYAN)%s$(END)" \
		$(NAME) \
		$(shell echo "$(SRCS)" | tr " " "\n" | grep -n "$<" | cut -d : -f 1) \
		$(NUM_FILES) \
		$(shell echo $< | sed 's|$(SRCS_DIR)/||g')
	@$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

$(NAME): $(LIBS) $(OBJS)
	@printf "\r$(CLEAR)%-15s: $(GREEN)compilation finished$(END)\n" $(NAME)
	@$(CC) $(OBJS) $(LIBFLAGS) $(LIBS) -o $(NAME)
	@printf "%-15s: create $(NAME)\n" $(NAME)

.PHONY: all clean fclean re test norm lsp
.DEFAULT_GOAL := all
all: $(NAME)

clean:
	@make --directory=$(LIBFT_DIR) --no-print-directory clean
	@$(RM) -r $(OBJS_DIR)
	@printf "%-15s: remove $(OBJS_DIR)\n" $(NAME)

fclean:
	@make --directory=$(LIBFT_DIR) --no-print-directory fclean
	@$(RM) -r $(OBJS_DIR)
	@printf "%-15s: remove $(OBJS_DIR)\n" $(NAME)
	@$(RM) $(NAME)
	@printf "%-15s: remove $(NAME)\n" $(NAME)

re: fclean all

norm:
	@norminette $(INCLUDES_DIR) $(SRCS_DIR)

lsp: fclean
	@bear -- make --no-print-directory all
	@compdb list | sponge compile_commands.json


TESTS := $(patsubst $(SRCS_DIR)/%, $(TESTS_DIR)/%, $(SRCS))
TEST_UTILS := $(addprefix $(TESTS_DIR)/, \
	test.c \
)
test: $(NAME) $(TESTS) $(TEST_UTILS)
	@printf "%-15s: start unit test\n" $(LIBRARY)
	@$(RM) result.log
	@for test in $(TESTS); do \
		$(CC) $(CFLAGS) $(INCFLAGS) -I $(SRCS_DIR) "$$test" $(TEST_UTILS) $(NAME) -o "$${test%.c}_"; \
		test_name=$$(echo "$$test" | sed "s|$(TESTS_DIR)/||"); \
		printf "%-15s: $(CYAN)%-30s$(END) ... " $(NAME) "$$test_name"; \
		if valgrind --leak-check=full -q ./$${test%.c}_ 1>>result.log 2>&1; then \
			echo "$(GREEN)OK$(END)"; \
		else \
			echo "$(RED)KO (status: $$?)$(END)"; \
		fi; \
		$(RM) $${test%.c}_; \
	done;
	@printf "%-15s: end unit test\n" $(LIBRARY)
