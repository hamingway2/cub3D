/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 20:10:34 by gkhavari          #+#    #+#             */
/*   Updated: 2026/09/29 20:10:57 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include "mlx.h"

// Macro Definition
# define TRUE 1
# define FALSE 0
# define USAGE_INFO "Usage: ./cub3d maps/<map.cub>\n"
# define HELP_FLAG "--help"
# define EXTENSION ".cub"
# define BUFFER_SIZE 42

//Error msg
# define ERROR "Error\n"
# define INVALID_FILENAME "Invalid file name\n"
# define WRONG_EXTENSION "Invalid file extension\n"
# define OPEN_ERROR "Failed to open file\n"
# define INVALID_LINE "Invalid line detected\n"
# define NO_PLAYER_START "No player start position found in the map\n"
# define MULTIPLE_PLAYER_STARTS "Multiple player start positions found in the map\n"
# define INVALID_CONFIG_LINE "Invalid configuration line\n"
# define DUPLICATE_TEXTURE "Duplicate texure line\n"
# define DUPLICATE_COLOR "Duplicate color line\n"
# define INVALID_MAP_WALLS "Map is not surrounded by walls\n"
# define INVALID_MAP_CHARACTER "Invalid character in map\n"
# define INVALID_MAP "Invalid map\n"
# define MALLOC_ERROR "Malloc faild\n"

//Map elements
# define WALL '1'
# define EMPTY '0'
# define PLAYER_NORTH 'N'
# define PLAYER_SOUTH 'S'
# define PLAYER_WEST 'W'
# define PLAYER_EAST 'E'

//KEY CODES
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_UP 65362
# define KEY_RIGHT 65363
# define KEY_DOWN 65364

typedef struct s_parse
{
	int	map_started;
	int	map_height;
	int	capacity;
}	t_parse;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	direction; // 0 = North, 90 = East, 180 = South, 270 = West
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	char		*texture_north;
	char		*texture_south;
	char		*texture_west;
	char		*texture_east;
	char		*floor_color; // als int[3] parsen
	char		*ceiling_color; // als int[3] parsen
	t_map		map;
	t_player	player;
	t_img		img;
}	t_game;

void	game_init(t_game *game);
int		parse_file(t_game *game, char *filename);
void	game_destroy(t_game *game, int exit_code);
int		error_msg(char *msg);
char	*get_next_line(int fd);
int		is_empty_line(char *line);
int		is_config_line(char *line);
int		is_map_line(char *line);
int		is_texture_line(char *line);
int		is_color_line(char *line);
int		is_player_char(char c);
int		parse_config(t_game *game, char *line);
int		parse_map(t_game *game, char *filename);
int		ft_max(int a, int b);
int		get_line_length(char *line);
int		player_init(t_game *game);
int		key_event(int key, t_game *game);
void	game_cleanup(t_game *game);
int		game_close(t_game *game);
int		validate_map(t_game *game);
int		get_real_map_height(t_map *map);
void	print_game(t_game *game);
int		check_arguments(int ac, char **av);
void	free_map(t_map *map);
int		normalize_map(t_map *map);

#endif
