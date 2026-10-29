/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 15:22:15 by azielnic          #+#    #+#             */
/*   Updated: 2026/10/12 19:16:31 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_background(t_game *game)
{
	int		y;
	int		x;
	int		colour;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		colour = 0x564F43;
		if (y <= HEIGHT / 2)
			colour = 0xBDE0FE;
		while (x < WIDTH)
		{
			put_pixel(x, y, colour, game);
			x++;
		}
		y++;
	}
}

void	clear_image(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0x000000, game);
			x++;
		}
		y++;
	}
}

void	draw_square(t_game *game, t_square square)
{
	int	i;
	int	j;

	i = 0;
	while (i < square.size)
	{
		j = 0;
		while (j < square.size)
		{
			put_pixel(square.x + i, square.y + j, square.colour, game);
			j++;
		}
		i++;
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
