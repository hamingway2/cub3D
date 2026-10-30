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

static t_minimap_range	get_visible_range(double player_pos, int viewport_size,
		int map_size)
{
	t_minimap_range	range;

	range.start = (int)floor(player_pos
			- viewport_size / (2.0 * MINIMAP_CELL_SIZE));
	range.end = (int)ceil(player_pos
			+ viewport_size / (2.0 * MINIMAP_CELL_SIZE));
	if (range.start < 0)
		range.start = 0;
	if (range.end > map_size)
		range.end = map_size;
	return (range);
}

void	init_minimap(t_game *game, t_minimap *minimap)
{
	minimap->game = game;
	minimap->width = game->screen_width / MINIMAP_WINDOW_DIVISOR;
	minimap->height = game->screen_height / MINIMAP_WINDOW_DIVISOR;
	if (minimap->width < 1)
		minimap->width = 1;
	if (minimap->height < 1)
		minimap->height = 1;
	minimap->origin.x = MINIMAP_X + minimap->width / 2
		- (int)(game->player.x * MINIMAP_CELL_SIZE);
	minimap->origin.y = MINIMAP_Y + minimap->height / 2
		- (int)(game->player.y * MINIMAP_CELL_SIZE);
	if (game->map.width * MINIMAP_CELL_SIZE <= minimap->width)
		minimap->origin.x = MINIMAP_X;
	if (game->map.height * MINIMAP_CELL_SIZE <= minimap->height)
		minimap->origin.y = MINIMAP_Y;
	minimap->horizontal = get_visible_range(game->player.x,
			minimap->width, game->map.width);
	minimap->vertical = get_visible_range(game->player.y,
			minimap->height, game->map.height);
}

static void	draw_grid_cell(t_minimap *minimap, int x, int y)
{
	int				i;
	t_minimap_point	point;

	minimap_map_to_screen(minimap, x, y, &point);
	i = 0;
	while (i < MINIMAP_CELL_SIZE)
	{
		draw_minimap_pixel(minimap, point.x + i, point.y, 0xC5C6C7);
		draw_minimap_pixel(minimap, point.x, point.y + i, 0xC5C6C7);
		if (x == minimap->game->map.width - 1)
			draw_minimap_pixel(minimap, point.x + MINIMAP_CELL_SIZE,
				point.y + i, 0xC5C6C7);
		if (y == minimap->game->map.height - 1)
			draw_minimap_pixel(minimap, point.x + i,
				point.y + MINIMAP_CELL_SIZE, 0xC5C6C7);
		i++;
	}
}

void	draw_minimap_grid(t_minimap *minimap)
{
	int	x;
	int	y;

	y = minimap->vertical.start;
	while (y < minimap->vertical.end)
	{
		x = minimap->horizontal.start;
		while (x < minimap->horizontal.end)
		{
			draw_grid_cell(minimap, x, y);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_game *game)
{
	t_minimap	minimap;

	init_minimap(game, &minimap);
	draw_minimap_walls(&minimap);
	draw_minimap_grid(&minimap);
	draw_player_rays(&minimap);
	draw_minimap_player(&minimap);
	draw_minimap_border(&minimap);
}
