/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 17:12:00 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/30 17:12:00 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Calculates elapsed time since the previous frame. */
static double	get_frame_delta(void)
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
	return (frame_delta);
}

/*
 * Handles pending window resizing and renders a frame using elapsed time
 * to keep player movement consistent across frame rates.
 */
int	draw_loop(t_game *game)
{
	double	frame_delta;

	if (game->resize_requested)
	{
		game->resize_requested = false;
		resize_game_window(game);
	}
	frame_delta = get_frame_delta();
	clear_image(game);
	rotate_player(&game->player, frame_delta);
	move_player(&game->player, game, frame_delta);
	draw_background(game);
	draw_raycasting(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->window, game->img.img, 0, 0);
	return (0);
}
