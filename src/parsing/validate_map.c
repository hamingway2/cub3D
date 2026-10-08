/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 15:14:24 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/08 15:14:26 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_wall_direction(t_map *map, int i, int j, int direction[2])
{
	while (i >= 0 && i < map->height
		&& j >= 0 && j < map->width)
	{
		if (map->grid[i][j] == '1')
			return (TRUE);
		if (map->grid[i][j] == ' ')
			return (FALSE);
		i += direction[0];
		j += direction[1];
	}
	return (FALSE);
}

static int	is_walkable_tile(char tile)
{
	return (tile == '0' || is_player_char(tile));
}

static int	check_cell_walls(t_map *map, int i, int j)
{
	static int	directions[4][2] = {
	{-1, 0},
	{1, 0},
	{0, -1},
	{0, 1}
	};
	int			d;

	d = 0;
	while (d < 4)
	{
		if (!check_wall_direction(map, i, j, directions[d]))
			return (FALSE);
		d++;
	}
	return (TRUE);
}

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
			if (is_walkable_tile(game->map.grid[i][j])
				&& !check_cell_walls(&game->map, i, j))
			{
				game_cleanup(game);
				return (error_msg(INVALID_MAP_WALLS));
			}
			j++;
		}
		i++;
	}
	return (TRUE);
}

static int	is_valid_map_character(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ');
}

static int	validate_map_characters(t_game *game)
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
			{
				game_cleanup(game);
				return (error_msg(INVALID_MAP_CHARACTER));
			}
			j++;
		}
		i++;
	}
	return (TRUE);
}

int	validate_map(t_game *game)
{
	if (validate_map_walls(game) == FALSE)
	{
		return (FALSE);
	}
	if (validate_map_characters(game) == FALSE)
	{
		return (FALSE);
	}
	return (TRUE);
}
