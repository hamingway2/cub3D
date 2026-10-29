/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_defines.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 19:58:44 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/27 19:58:46 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_DEFINES_H
# define CUB3D_DEFINES_H

# define TRUE 1
# define FALSE 0
# define USAGE_INFO "Usage: ./cub3d <map.cub>\n"
# define HELP_FLAG "--help"
# define EXTENSION ".cub"
# define BUFFER_SIZE 42
# define PI 3.14159265359
# define FOV 60.0

# define WIDTH 1920
# define HEIGHT 1080
# define PLAYER_RADIUS 0.1
# define PLAYER_SPEED 3.0
# define TURN_SPEED 90.0

# define MINIMAP_X 20
# define MINIMAP_Y 20
# define MINIMAP_WIDTH 300
# define MINIMAP_HEIGHT 300

# define ERROR "Error\n"
# define WRONG_EXTENSION "Invalid map file extension (expected .cub)\n"
# define OPEN_ERROR "Could not open map file\n"
# define EMPTY_FILE "Map file is empty\n"
# define FILE_READ_ERROR "Could not read map file\n"
# define INVALID_LINE "Invalid line in map file:\n"
# define NO_PLAYER_START "Map must contain a player start (N, S, E, or W)\n"
# define MULTIPLE_PLAYER_STARTS "Map contains more than one player start\n"
# define INVALID_CONFIG_LINE "Invalid config: expected NO/SO/WE/EA texture " \
	"or F/C color\n"
# define DUPLICATE_CONFIG_LINE "Duplicate config line: "
# define MISSING_CONFIG_LINES "Missing config line(s):\n"
# define CONFIG_AFTER_MAP "Configuration lines must appear before the map\n"
# define INVALID_COLOR_VALUE "Invalid color: expected R,G,B values " \
	"from 0 to 255\n"
# define INVALID_MAP_WALLS "Map is open: every walkable tile must be " \
	"enclosed by walls\n"
# define INVALID_MAP_CHARACTER "Invalid map character at row "
# define INVALID_MAP_COLUMN ", column "
# define INVALID_MAP "Map section is missing or empty\n"
# define MALLOC_ERROR "Memory allocation failed\n"

# define WALL '1'
# define EMPTY '0'
# define PLAYER_NORTH 'N'
# define PLAYER_SOUTH 'S'
# define PLAYER_WEST 'W'
# define PLAYER_EAST 'E'

# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_UP 65362
# define KEY_RIGHT 65363
# define KEY_DOWN 65364
# define W 119
# define A 97
# define S 115
# define D 100

#endif
