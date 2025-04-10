TESTS := $(patsubst $(SRCS_DIR)/%, $(TESTS_DIR)/%, $(SRCS))

.PONY: test

test: $(OBJS) $(TEST_OBJS) $(LIBFT)
	@printf "%-15s: start unit test\n" $(NAME)
	@$(RM) result.log
	@for test in $(TESTS); do \
		$(CC) $(CFLAGS) $(INCFLAGS) -I $(SRCS_DIR) -c "$$test" -o "$${test%.c}.o"; \
		$(CC) "$${test%.c}.o" $(filter-out %main.o, $(OBJS)) $(LIBFLAGS) $(LIBS) -o "$${test%.c}_"; \
		test_name=$$(echo "$$test" | sed "s|$(TESTS_DIR)/||"); \
		printf "%-15s: $(CYAN)%-30s$(END) ... " $(NAME) "$$test_name"; \
		if valgrind --leak-check=full -q ./$${test%.c}_ 1>>result.log 2>&1; then \
			echo "$(GREEN)OK$(END)"; \
		else \
			echo "$(RED)KO (status: $$?)$(END)"; \
		fi; \
		$(RM) $${test%.c}.o; \
		$(RM) $${test%.c}_; \
	done;
	@printf "%-15s: end unit test\n" $(NAME)

