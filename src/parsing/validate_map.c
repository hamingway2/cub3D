#include "cub3d.h"

static int	check_wall_direction(t_map *map, int i, int j, int di, int dj)
{
	while (i >= 0 && i < map->height
		&& j >= 0 && j < map->width)
	{
		if (map->grid[i][j] == '1')
			return (TRUE);
		i += di;
		j += dj;
	}
	return (FALSE);
}

/**
Validate that the map is surrounded by walls ('1') in all four directions, 
not assuming the map is rectangular. This function checks each cell in the map grid 
and ensures that if it is a '0' or a player position, there are walls in all four cardinal 
directions (up, down, left, right). If any of these checks fail, it returns an error message 
indicating that the map walls are invalid.
*/
static int	validate_map_walls(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.grid[i][j] == '0'
				|| is_player_char(game->map.grid[i][j]))
			{
				if (!check_wall_direction(&game->map, i, j, -1, 0)
					|| !check_wall_direction(&game->map, i, j, 1, 0)
					|| !check_wall_direction(&game->map, i, j, 0, -1)
					|| !check_wall_direction(&game->map, i, j, 0, 1))
					return (error_msg(INVALID_MAP_WALLS));
			}
			j++;
		}
		i++;
	}
	return (TRUE);
}

static int is_valid_map_character(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

static int validate_map_characters(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.grid[i])
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (!is_valid_map_character(game->map.grid[i][j]))
				return (error_msg(INVALID_MAP_CHARACTER));
			j++;
		}
		i++;
	}
	return (TRUE);
}

int validate_map(t_game *game)
{
	if (validate_map_walls(game) == FALSE)
		return (FALSE);
	if (validate_map_characters(game) == FALSE)
		return (FALSE);
	return (TRUE);
}