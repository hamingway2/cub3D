SRC := src/main.c \
		src/get_next_line.c \
		src/utils.c \
		src/check_input.c \
		src/testing_functions.c \
		src/init/game_init.c \
		src/init/game_destroy.c \
		src/init/player_init.c \
		src/parsing/parse_file.c \
		src/parsing/parse_config.c \
		src/parsing/parse_map.c \
		src/parsing/parse_config_utils.c \
		src/parsing/parse_map_config.c \
		src/parsing/validate_map.c \
		src/event/event.c \

NAME := cub3d
CC := cc
CFLAGS := -Wall -Wextra -Werror -I Libft/include -I includes
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
