/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 18:52:29 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/30 18:52:29 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Converts map coordinates to pixels using the current minimap origin. */
void	minimap_map_to_screen(t_minimap *minimap, double map_x, double map_y,
		t_minimap_point *screen_point)
{
	screen_point->x = minimap->origin.x
		+ (int)(map_x * MINIMAP_CELL_SIZE);
	screen_point->y = minimap->origin.y
		+ (int)(map_y * MINIMAP_CELL_SIZE);
}

/* Draws a pixel only when it falls inside the minimap viewport. */
void	draw_minimap_pixel(t_minimap *minimap, int x, int y, int colour)
{
	if (x >= MINIMAP_X && x < MINIMAP_X + minimap->width
		&& y >= MINIMAP_Y && y < MINIMAP_Y + minimap->height)
		put_pixel(x, y, colour, minimap->game);
}

/* Draws the viewport outline over the minimap contents. */
void	draw_minimap_border(t_minimap *minimap)
{
	int	i;

	i = 0;
	while (i < minimap->width)
	{
		draw_minimap_pixel(minimap, MINIMAP_X + i, MINIMAP_Y, 0xFFFFFF);
		draw_minimap_pixel(minimap, MINIMAP_X + i,
			MINIMAP_Y + minimap->height - 1, 0xFFFFFF);
		i++;
	}
	i = 0;
	while (i < minimap->height)
	{
		draw_minimap_pixel(minimap, MINIMAP_X, MINIMAP_Y + i, 0xFFFFFF);
		draw_minimap_pixel(minimap, MINIMAP_X + minimap->width - 1,
			MINIMAP_Y + i, 0xFFFFFF);
		i++;
	}
}

/* Fills one wall tile, clipping its pixels to the minimap viewport. */
static void	draw_minimap_tile(t_minimap *minimap, int map_x, int map_y,
		int colour)
{
	t_minimap_point	point;
	int				x;
	int				y;

	minimap_map_to_screen(minimap, map_x, map_y, &point);
	y = point.y;
	while (y < point.y + MINIMAP_CELL_SIZE)
	{
		x = point.x;
		while (x < point.x + MINIMAP_CELL_SIZE)
		{
			draw_minimap_pixel(minimap, x, y, colour);
			x++;
		}
		y++;
	}
}

/* Draws wall tiles within the visible map ranges. */
void	draw_minimap_walls(t_minimap *minimap)
{
	int	x;
	int	y;

	y = minimap->vertical.start;
	while (y < minimap->vertical.end)
	{
		x = minimap->horizontal.start;
		while (x < minimap->horizontal.end)
		{
			if (minimap->game->map.grid[y][x] == '1')
				draw_minimap_tile(minimap, x, y, 0x708090);
			x++;
		}
		y++;
	}
}
