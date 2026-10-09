/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 16:49:07 by azielnic          #+#    #+#             */
/*   Updated: 2026/10/09 22:12:38 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	distance(double x, double y)
{
	return (sqrt(x * x + y * y));
}

static void	draw_walls(t_game *game, double ray_angle, int screen_x)
{
	double	ray_x;
	double	ray_y;
	double	angle;
	double	dist;
	double	height;
	double	projection_plane;
	int		start_y;
	int		end_y;
	int		y;

	angle = ray_angle * PI / 180.0;
	ray_x = game->player.x;
	ray_y = game->player.y;
	while (!collision(ray_x, ray_y, game))
	{
		ray_x += sin(angle) * 0.02;
		ray_y -= cos(angle) * 0.02;
	}

	dist = distance(ray_x - game->player.x, ray_y - game->player.y);
	dist *= cos((ray_angle - game->player.direction) * PI / 180.0);
	if (dist < 0.001)
		dist = 0.001;
	projection_plane = (WIDTH / 2.0);
	height = projection_plane / dist;
	start_y = (HEIGHT - (int)height) / 2;
	end_y = start_y + (int)height;
	if (start_y < 0)
		start_y = 0;
	if (end_y >= HEIGHT)
		end_y = HEIGHT - 1;
	y = start_y;
	while (y <= end_y)
	{
		put_pixel(screen_x, y, 0x0000FF, game);
		y++;
	}
}

void	draw_raycasting(t_game *game)
{
	double	angle;
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		angle = game->player.direction - FOV / 2.0 + FOV * x / (WIDTH - 1.0);
		draw_walls(game, angle, x);
		x++;
	}
}
