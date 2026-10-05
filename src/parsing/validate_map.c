#include "cub3d.h"

static int validate_map_walls(t_game *game)
{
	int	i;
	int	j;

	//check top and bottom walls
	i = 0;
	while (i < game->map.width)
	{
		if (game->map.grid[0][i] != '1' || game->map.grid[game->map.height - 1][i] != '1')
			return (error_msg(INVALID_MAP_WALLS));
		i++;
	}
	//check left and right walls
	j = 0;
	while (j < game->map.height)
	{
		if (game->map.grid[j][0] != '1' || game->map.grid[j][game->map.width - 1] != '1')
			return (error_msg(INVALID_MAP_WALLS));
		j++;
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