SRC := src/main.c \
		src/get_next_line.c \
		src/utils.c \
		src/init/game_init.c \
		src/init/game_destroy.c \
		src/init/player_init.c \
		src/parsing/parse_file.c \
		src/parsing/parse_config.c \
		src/parsing/parse_map.c \
		src/parsing/parsing_utils.c \
		src/event/event.c \
		src/rendering/drawing.c \

NAME := cub3d
CC := cc
CFLAGS := -Wall -Wextra -Werror -I Libft/include -I includes
MLXFLAGS = -lmlx -lXext -lX11 -lm  # -lm for the math library

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

%.o: %.c
	@$(CC) $(CFLAGS) -Iincludes -c $< -o $@

clean:
	@rm -f $(OBJ)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re debug $(LIBFT)