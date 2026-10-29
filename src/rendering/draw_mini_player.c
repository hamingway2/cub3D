/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 19:10:54 by azielnic          #+#    #+#             */
/*   Updated: 2026/10/12 19:13:13 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_player_ray(t_game *game, int cell_size, double ray_angle)
{
	double	ray_x;
	double	ray_y;
	double	step;
	int		screen_x;
	int		screen_y;

	ray_x = game->player.x;
	ray_y = game->player.y;
	step = 0.02;
	while (!collision(ray_x, ray_y, game))
	{
		screen_x = MINIMAP_X + (int)(ray_x * cell_size);
		screen_y = MINIMAP_Y + (int)(ray_y * cell_size);
		put_pixel(screen_x, screen_y, 0xFF0000, game);
		ray_x += sin(ray_angle * PI / 180.0) * step;
		ray_y -= cos(ray_angle * PI / 180.0) * step;
	}
}

void	draw_player_rays(t_game *game, int cell_size)
{
	double	ray_direction;
	double	angle;
	int		i;

	ray_direction = game->player.direction;
	i = 0;
	while (i < WIDTH)
	{
		angle = ray_direction - FOV / 2.0 + FOV * i / (WIDTH - 1);
		draw_player_ray(game, cell_size, angle);
		i++;
	}
}

void	draw_minimap_player(t_game *game, int cell_size)
{
	int		player_x;
	int		player_y;

	player_x = MINIMAP_X + (int)(game->player.x * cell_size);
	player_y = MINIMAP_Y + (int)(game->player.y * cell_size);
	draw_square(game, (t_square){player_x - 5, player_y - 5, 10, 0x00FF00});
}
