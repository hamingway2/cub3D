/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 16:49:07 by azielnic          #+#    #+#             */
/*   Updated: 2026/10/07 22:07:33 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	draw_player_ray(t_game *game, int cell_size, int offset_y, int offset_x)
{
	double	ray_x;
	double	ray_y;
	double	angle;
	double	step;
	int		screen_x;
	int		screen_y;

	angle = game->player.direction * PI / 180.0;
	ray_x = game->player.x;
	ray_y = game->player.y;
	step = 0.02;

	while (!collision_minimap(ray_x, ray_y, game))
	{
		screen_x = offset_x + (int)(ray_x * cell_size);
		screen_y = offset_y + (int)(ray_y * cell_size);
		put_pixel(screen_x, screen_y, 0xFF0000, game);
		ray_x += sin(angle) * step;
		ray_y += cos(angle) * step;

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

static void	draw_horizontal_grid(t_game *game, int cell_size, int offset_x, int offset_y)
{
	int	x;
	int	y;
	
	y = 0;
	while (y <= game->map.height)
	{
		x = 0;
		while (x < game->map.width * cell_size)
		{
			put_pixel(offset_x + x, offset_y + y * cell_size, 0xC5C6C7, game);
			x++;
		}
		y++;
	}
}

static void	draw_vertical_grid(t_game *game, int cell_size, int offset_x, int offset_y)
{
	int	x;
	int	y;
	
	x = 0;
	while (x <= game->map.width)
	{
		y = 0;
		while (y < game->map.height * cell_size)
		{
			put_pixel(offset_x + x * cell_size, offset_y + y, 0xC5C6C7, game);
			y++;
		}
		x++;
	}
}

static void	draw_grid(t_game *game, int cell_size, int offset_x, int offset_y)
{
	draw_horizontal_grid(game, cell_size, offset_x, offset_y);
	draw_vertical_grid(game, cell_size, offset_x, offset_y);
}

static void	draw_map_row(t_game *game, t_map *map, int y, int cell_size, int offset_x, int offset_y)
{
	int	x;

	x = 0;
	while (map->grid[y][x] && map->grid[y][x] != '\n')
	{
		if (map->grid[y][x] == '1')
		{
			draw_square(offset_x + x * cell_size, offset_y + y * cell_size, cell_size, 0x708090, game);
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
	// int		rendered_width;
	// int		rendered_height;
	int		y;
	
	map = &game->map;
	cell_size = (int)get_minimap_scale(map);
	// rendered_width = map->width * cell_size;
	// rendered_height = map->height * cell_size;
	offset_x = MINIMAP_X;
	offset_y = MINIMAP_Y;
	y = 0;
	while (y < map->height)
	{
		draw_map_row(game, map, y, cell_size, offset_x, offset_y);
		y++;
	}
	draw_grid(game, cell_size, offset_x, offset_y);
	draw_player_ray(game, cell_size, offset_x, offset_y);
	draw_minimap_player(game, cell_size, offset_x, offset_y);
}
