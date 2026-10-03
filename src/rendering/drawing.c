/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 15:22:15 by azielnic          #+#    #+#             */
/*   Updated: 2026/10/03 16:28:37 by azielnic         ###   ########.fr       */
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

void	draw_map(t_game	*game)
{
	t_map	*map;
	int	y;
	int	x;

	map = &game->map;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x] && map->grid[y][x] != '\n')
		{
			if (map->grid[y][x] == '1')
				draw_square(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, 0xFFFF00, game);
			x++;
		}
		y++;
	}
}

void	put_pixel(int x, int y, int colour, t_game *game)
{
	int	index;
		
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->img.line_length + x * game->img.bits_per_pixel / 8;
	*(unsigned int *)(game->img.addr + index) = colour;
}
