SRC := src/main.c \


NAME := cub3d
CC := cc
CFLAGS := -Wall -Wextra -Werror -I Libft/include -I includes

OBJ := $(SRC:.c=.o)

# LIBFT_DIR := Libft
# LIBFT := $(LIBFT_DIR)/libft.a

.SILENT: all $(NAME)

all: $(LIBFT) $(NAME)

debug:
	$(MAKE) CFLAGS="$(CFLAGS) -g" re

$(LIBFT):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -Iincludes -c $< -o $@

clean:
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re debug $(LIBFT)
