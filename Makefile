include makefiles/minishell.mk

.PHONY: all clean fclean re norm lsp analyze
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

analyze:
	@clang-tidy --quiet $(SRCS)
