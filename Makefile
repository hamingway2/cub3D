SRC := src/main.c \
		src/init/game_init.c \
		src/init/init_textures.c \
		src/parsing/parse_file.c \
		src/parsing/parse_file_read.c \
		src/parsing/validate_config.c \
		src/parsing/parse_config.c \
		src/parsing/parse_color.c \
		src/parsing/parse_map.c \
		src/parsing/parse_config_utils.c \
		src/parsing/parse_map_utils.c \
		src/parsing/validate_map.c \
		src/parsing/validate_map_walls.c \
		src/utils/get_next_line.c \
		src/utils/get_next_line_utils.c \
		src/utils/check_input.c \
		src/utils/error.c \
		src/utils/game_destroy.c \
		src/event/event.c \
		src/rendering/drawing.c \
		src/rendering/draw_minimap.c \
		src/rendering/draw_mini_player.c \
		src/player/movement.c \
		src/player/movement_vector.c \
		src/raycasting/raycasting.c \
		src/raycasting/ray_setup.c \
		src/raycasting/texture_mapping.c

NAME := cub3d
CC := cc
CFLAGS := -Wall -Wextra -Werror -I libft -I includes
MLXFLAGS = -lmlx -lXext -lX11 -lm  # -lm for the math library

MLX_DIR = minilibx-linux
MLX     = -L$(MLX_DIR) -lmlx_Linux
MLX_INC = -I$(MLX_DIR)
MLX_LIBS= -lXext -lX11 -lm -lz

OBJ := $(SRC:.c=.o)

LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a

.SILENT: all $(NAME)

all: $(LIBFT) $(NAME)

$(OBJ): includes/cub3d.h includes/cub3d_defines.h includes/cub3d_structs.h \
		includes/cub3d_game.h includes/cub3d_parsing.h includes/cub3d_render.h

src/get_next_line.o src/get_next_line_utils.o: includes/get_next_line_internal.h

debug:
	$(MAKE) CFLAGS="$(CFLAGS) -g" re

$(LIBFT):
	@$(MAKE) -s --no-print-directory -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
#	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) $(MLX_LIBS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -Iincludes -c $< -o $@
#	@$(CC) $(CFLAGS) $(MLX_INC)  -Iincludes -c $< -o $@

clean:
	@rm -f $(OBJ)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re debug $(LIBFT)
