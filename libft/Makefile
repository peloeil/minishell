include common.mk

LIBRARY := libft
NAME := $(LIBRARY).a
SRCS := $(addprefix $(SRCS_DIR)/, \
	$(addprefix ctype/, \
		isalnum.c \
		isalpha.c \
		isascii.c \
		isdigit.c \
		isprint.c \
		isspace.c \
		tolower.c \
		toupper.c \
	) \
	$(addprefix list/, \
		push_back.c \
		push_front.c \
		pop_back.c \
		pop_front.c \
		clear.c \
		delete.c \
		iter.c \
		last.c \
		map.c \
		new.c \
		size.c \
	) \
	$(addprefix stdlib/, \
		atoi.c \
		calloc.c \
		itoa.c \
	) \
	$(addprefix string/, \
		bzero.c \
		memchr.c \
		memcmp.c \
		memcpy.c \
		memmove.c \
		memset.c \
		split.c \
		strchr.c \
		strcmp.c \
		strdup.c \
		striteri.c \
		strjoin.c \
		strlcat.c \
		strlcpy.c \
		strlen.c \
		strmapi.c \
		strncmp.c \
		strndup.c \
		strnstr.c \
		strrchr.c \
		strtrim.c \
		substr.c \
	) \
	$(addprefix std_string/, \
		new.c \
		with_capacity.c \
		from.c \
		reserve.c \
		push.c \
		push_str.c \
		pop.c \
		insert.c \
		starts_with.c \
		ends_with.c \
		find.c \
		rfind.c \
	) \
	$(addprefix stdio/, \
		$(addprefix printf/, \
			push_char.c \
			push_str.c \
			push_int.c \
			push_uint.c \
			push_hex.c \
		) \
		vdprintf.c \
		vprintf.c \
		vsprintf.c \
		vsnprintf.c \
		vasprintf.c \
		dprintf.c \
		printf.c \
		sprintf.c \
		snprintf.c \
		asprintf.c \
		getc.c \
		getdelim.c \
		getline.c \
	) \
)
OBJS := $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))
INCLUDES := $(addprefix $(INCLUDES_DIR)/, \
	$(addprefix $(LIBRARY)/, \
		ft_ctype.h \
		ft_list.h \
		ft_stdlib.h \
		ft_stdio.h \
		ft_string.h \
		std_string.h \
	) \
)
NUM_FILES := $(words $(SRCS))

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(INCLUDES)
	@mkdir -p $(@D)
	@printf \
		"\r$(CLEAR)%-15s: [%2d/%2d] $(GREEN)compiling $(CYAN)%s$(END)" \
		$(LIBRARY) \
		$(shell echo "$(SRCS)" | tr " " "\n" | grep -n "$<" | cut -d : -f 1) \
		$(NUM_FILES) \
		$(shell echo $< | sed 's|$(SRCS_DIR)/||g')
	@$(CC) $(CFLAGS) -I $(INCLUDES_DIR) -c $< -o $@

$(NAME): $(OBJS)
	@printf "\r$(CLEAR)%-15s: $(GREEN)compilation finished$(END)\n" $(LIBRARY)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	@printf "%-15s: create $(NAME)\n" $(LIBRARY)

.PHONY: all clean fclean re test
all: $(NAME)

clean:
	@$(RM) -r $(OBJS_DIR)
	@printf "%-15s: remove $(OBJS_DIR)\n" $(LIBRARY)

fclean: clean
	@$(RM) $(NAME)
	@printf "%-15s: remove $(NAME)\n" $(LIBRARY)

re: fclean all

TESTS := $(patsubst $(SRCS_DIR)/%, $(TESTS_DIR)/%, $(SRCS))
TEST_UTILS := $(addprefix $(TESTS_DIR)/, \
	test.c \
)
test: $(NAME) $(TESTS) $(TEST_UTILS)
	@printf "%-15s: start test\n" $(LIBRARY)
	@$(RM) result.log
	@for test in $(TESTS); do \
		$(CC) $(CFLAGS) -I $(INCLUDES_DIR) -I $(SRCS_DIR) "$$test" $(TEST_UTILS) $(NAME) -o "$${test%.c}_"; \
		test_name=$$(echo "$$test" | sed "s|$(TESTS_DIR)/||"); \
		printf "%-15s: $(CYAN)%-30s$(END) ... " $(LIBRARY) "$$test_name"; \
		if valgrind --leak-check=full -q ./$${test%.c}_ 1>>result.log 2>&1; then \
			echo "$(GREEN)OK$(END)"; \
		else \
			echo "$(RED)KO (status: $$?)$(END)"; \
		fi; \
		$(RM) $${test%.c}_; \
	done;
	@printf "%-15s: end test\n" $(LIBRARY)
