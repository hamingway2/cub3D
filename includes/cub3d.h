#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>
# include <math.h>
# include "mlx.h"

// Macro definition
# define TRUE 1
# define FALSE 0
# define USAGE_INFO "Usage: ./cub3d maps/<map.cub>\n"
# define HELP_FLAG "--help"
# define EXTENSION ".cub"
# define BUFFER_SIZE 42
# define PI 3.14159265359

// Scaling
# define WIDTH 1920
# define HEIGHT 1080
# define PLAYER_RADIUS 0.1
# define PLAYER_SPEED 3.0
# define TURN_SPEED 90.0

// Minimap dimensions
# define MINIMAP_X 20	// position of minimap in game window
# define MINIMAP_Y 20	// position of minimap in game window
# define MINIMAP_WIDTH 300
# define MINIMAP_HEIGHT 300

// Error msg
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

// Map elements
# define WALL '1'
# define EMPTY '0'
# define PLAYER_NORTH 'N'
# define PLAYER_SOUTH 'S'
# define PLAYER_WEST 'W'
# define PLAYER_EAST 'E'

// Key codes
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_UP 65362
# define KEY_RIGHT 65363
# define KEY_DOWN 65364
# define W 119
# define A 97
# define S 115
# define D 100

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
	int		bits_per_pixel;	// how many bits make up one pixel
	int		line_length;	// how many bytes make up one image row
	int		endian;			// how the bytes are ordered in memory
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

	bool	key_up;
	bool	key_down;
	bool	key_right;
	bool	key_left;
	bool	key_turn_left;
	bool	key_turn_right;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	char		*texture_north;
	char		*texture_south;
	char		*texture_west;
	char		*texture_east;
	int	 		floor_color;
	int			ceiling_color;
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
int		get_line_length(char *line);
int		player_init(t_game *game);
int		key_event(int key, t_game *game);
void	game_cleanup(t_game *game);
int		key_release(int key, t_game *game);
int		game_close(t_game *game);
int		validate_map(t_game *game);
void	print_game(t_game *game);
int		check_arguments(int ac, char **av);
void	free_map(t_map *map);
int		normalize_map(t_map *map);
int		game_setup(t_game *game, char *file);
void	game_loop(t_game *game);

//execution part
int		draw_loop(t_game *game);
void	put_pixel(int x, int y, int colour, t_game *game);
void	draw_square(int x, int y, int size, int colour, t_game *game);
// void	draw_map(t_game *game);
void	draw_minimap(t_game *game);
void	rotate_player(t_player *player, double delta_time);
void	move_player(t_player *player, t_game *game, double delta_time);
bool	collision_minimap(double x, double y, t_game *game);
void	clear_image(t_game *game);

#endif
