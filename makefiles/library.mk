# libft
LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a
$(LIBFT):
	@make --directory=$(LIBFT_DIR) --no-print-directory all

# minilibx
MLX_DIR := mlx_linux
MLX := $(MLX_DIR)/libmlx_Linux.a
MLXFLAGS := -O3 -lX11 -lXext -lm
$(MLX):
	@make --directory=$(MLX_DIR) --no-print-directory all 1>/dev/null
	@printf "\r$(CLEAR)%-15s: create $(MLX)\n" $(MLX_DIR)
