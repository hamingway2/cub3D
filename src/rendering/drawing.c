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

/*
 * Provides the main drawing loop, updating the game continuously by
 * calculating the time elapsed between frames and using it to ensure that 
 * player movement and rotation remain consistent regardless of the frame rate.
 *
 * Calculates the frame delta using the current time, clears the image, updates 
 * the player's rotation and movement, draws the background, renders the 3D 
 * scene using raycasting, and draws the minimap. 
 * Finally, displays the completed image in the window and returns 0 to keep 
 * the MiniLibX loop running.
 */

int	draw_loop(t_game *game)
{
	static struct timeval	last_frame_time;
	struct timeval			current_time;
	double					frame_delta;

	gettimeofday(&current_time, NULL);
	frame_delta = (double)current_time.tv_sec
		+ (double)current_time.tv_usec / 1000000.0;
	if (last_frame_time.tv_sec != 0 || last_frame_time.tv_usec != 0)
		frame_delta -= (double)last_frame_time.tv_sec
			+ (double)last_frame_time.tv_usec / 1000000.0;
	else
		frame_delta = 0.0;
	last_frame_time = current_time;
	clear_image(game);
	rotate_player(&game->player, frame_delta);
	move_player(&game->player, game, frame_delta);
	draw_background(game);
	draw_raycasting(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->window, game->img.img, 0, 0);
	return (0);
}

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
