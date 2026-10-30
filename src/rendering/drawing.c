/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 15:22:15 by azielnic          #+#    #+#             */
/*   Updated: 2026/10/29 18:50:36 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_background(t_game *game)
{
	int		y;
	int		x;
	int		colour;

	y = 0;
	while (y < game->screen_height)
	{
		x = 0;
		colour = game->floor_color;
		if (y <= game->screen_height / 2)
			colour = game->ceiling_color;
		while (x < game->screen_width)
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
	while (y < game->screen_height)
	{
		x = 0;
		while (x < game->screen_width)
		{
			put_pixel(x, y, 0x000000, game);
			x++;
		}
		y++;
	}
}

/*
 * Provides a reusable drawing function for creating filled squares, allowing 
 * other parts of the programme to draw shapes without repeating the logic for 
 * filling an area with pixels.
 *
 * Draws a filled square at the specified position using the given size and 
 * colour. Iterates over each pixel within the square and uses put_pixel to 
 * colour it, ensuring that pixels outside the screen boundaries are ignored.
 */

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

/*
 * Serves as a reusable, basic drawing operation for other functions, such as 
 * draw_square(), which uses it to draw larger shapes without duplicating the 
 * pixel-drawing logic.
 * 
 * Draws a pixel of the specified colour at the given coordinates. Checks 
 * that the coordinates are within the screen boundaries, then calculates 
 * the pixel's memory address using the image's line length and bits per 
 * pixel before writing the colour to the image data.
 */

void	put_pixel(int x, int y, int colour, t_game *game)
{
	int	index;

	if (x >= game->screen_width || y >= game->screen_height || x < 0 || y < 0)
		return ;
	index = y * game->img.line_length + x * game->img.bits_per_pixel / 8;
	*(unsigned int *)(game->img.addr + index) = colour;
}
