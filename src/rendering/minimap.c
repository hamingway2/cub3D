/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 16:49:07 by azielnic          #+#    #+#             */
/*   Updated: 2026/10/03 17:43:17 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_square(int x, int y, int size, int colour, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(x + i, y + j, colour, game);
			j++;
		}
		i++;
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

static void draw_minimap_player(t_game *game, int cell_size, int offset_x, int offset_y)
{
	int		player_x;
	int		player_y;

	player_x = offset_x + (int)(game->player.x * cell_size);
	player_y = offset_y + (int)(game->player.y * cell_size);
	draw_square(player_x - 5, player_y - 5, 10, 0x00FF00, game);
}

static void	draw_map_row(t_game *game, t_map *map, int y, int cell_size, int offset_x, int offset_y)
{
	int	x;

	x = 0;
	while (map->grid[y][x] && map->grid[y][x] != '\n')
	{
		if (map->grid[y][x] == '1')
		{
			draw_square(offset_x + x * cell_size, offset_y + y * cell_size, cell_size, 0xFFFF00, game);
		}
		x++;
	}
}

void	draw_minimap(t_game *game)
{
	t_map	*map;
	int		cell_size;
	int		offset_x;
	int		offset_y;
	int		rendered_width;
	int		rendered_height;
	int		y;
	
	map = &game->map;
	cell_size = (int)get_minimap_scale(map);
	rendered_width = map->width * cell_size;
	rendered_height = map->height * cell_size;
	offset_x = MINIMAP_X + (MINIMAP_WIDTH - rendered_width) / 2;
	offset_y = MINIMAP_Y + (MINIMAP_HEIGHT - rendered_height) / 2;
	y = 0;
	while (y < map->height)
	{
		draw_map_row(game, map, y, cell_size, offset_x, offset_y);
		y++;
	}
	draw_minimap_player(game, cell_size, offset_x, offset_y);
}
