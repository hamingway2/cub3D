/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 16:49:07 by azielnic          #+#    #+#             */
/*   Updated: 2026/10/12 19:12:37 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_horizontal_grid(t_game *game, int cell_size)
{
	int	x;
	int	y;

	y = 0;
	while (y <= game->map.height)
	{
		x = 0;
		while (x < game->map.width * cell_size)
		{
			put_pixel(MINIMAP_X + x, MINIMAP_Y + y * cell_size, 0xC5C6C7, game);
			x++;
		}
		y++;
	}
}

static void	draw_vertical_grid(t_game *game, int cell_size)
{
	int	x;
	int	y;

	x = 0;
	while (x <= game->map.width)
	{
		y = 0;
		while (y < game->map.height * cell_size)
		{
			put_pixel(MINIMAP_X + x * cell_size, MINIMAP_Y + y, 0xC5C6C7, game);
			y++;
		}
		x++;
	}
}

static void	draw_map_row(t_game *game, int y, int cell_size)
{
	t_map	*map;
	int		x;

	map = &game->map;
	x = 0;
	while (map->grid[y][x] && map->grid[y][x] != '\n')
	{
		if (map->grid[y][x] == '1')
		{
			draw_square(game, (t_square){MINIMAP_X + x * cell_size,
				MINIMAP_Y + y * cell_size, cell_size, 0x708090});
		}
		x++;
	}
}

static float	get_minimap_scale(t_map *map)
{
	float	scale_x;
	float	scale_y;

	scale_x = (float)MINIMAP_WIDTH / map->width;
	scale_y = (float)MINIMAP_HEIGHT / map->height;
	if (scale_x < scale_y)
		return (scale_x);
	return (scale_y);
}

void	draw_minimap(t_game *game)
{
	t_map	*map;
	int		cell_size;
	int		y;

	map = &game->map;
	cell_size = (int)get_minimap_scale(map);
	y = 0;
	while (y < map->height)
	{
		draw_map_row(game, y, cell_size);
		y++;
	}
	draw_horizontal_grid(game, cell_size);
	draw_vertical_grid(game, cell_size);
	draw_player_rays(game, cell_size);
	draw_minimap_player(game, cell_size);
}
