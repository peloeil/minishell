include makefiles/common.mk
include makefiles/library.mk

# binary name
NAME := minishell

SRCS := $(addprefix $(SRCS_DIR)/, \
	main.c \
	eval.c \
	command.c \
	$(addprefix wrappers/, \
		close.c \
		dup2.c \
		fork.c \
		pipe.c \
		open.c \
		stat.c \
		unlink.c \
		readline.c \
	) \
	$(addprefix env/, \
		free.c \
		ft_getenv.c \
		init.c \
		is_valid_key.c \
		search_key.c \
		split_char.c \
		update.c \
	) \
	$(addprefix error/, \
		free_strs.c \
		lexer.c \
		parser.c \
		execute.c \
	) \
	$(addprefix builtin/, \
		echo.c \
		env.c \
		exit.c \
		pwd.c \
		unset.c \
		utils.c \
		$(addprefix cd/, \
			cd.c \
			cd_utils.c \
		) \
		$(addprefix export/, \
			export.c \
			export_utils.c \
		) \
	) \
	$(addprefix lexer/, \
		lexer.c \
		operator.c \
		non_operator.c \
	) \
	$(addprefix parser/, \
		parse_tokens.c \
		parse_command.c \
		search_token.c \
	) \
	$(addprefix expand/, \
		expand.c \
		read_variable.c \
	) \
	$(addprefix execute/, \
		builtin.c \
		child.c \
		exec_args.c \
		execute.c \
		fd.c \
		exit_status.c \
		heredoc.c \
	) \
)
OBJS := $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

# includes
INCLUDES := $(addprefix $(INCLUDES_DIR)/, \
	$(addprefix $(NAME)/, \
		minishell.h \
		lexer.h \
		parser.h \
	) \
)
INCFLAGS := $(addprefix -I, \
	/usr/include \
	$(INCLUDES_DIR) \
	$(LIBFT_DIR)/$(INCLUDES_DIR) \
)

# libraries
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
