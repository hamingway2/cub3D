/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_walls.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 20:16:04 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/27 20:16:05 by gkhavari         ###   ########.fr       */
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

int	validate_map_walls(t_game *game)
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
				return (error_msg(INVALID_MAP_WALLS));
			}
			j++;
		}
		i++;
	}
	return (TRUE);
}
