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

/* Traces one field-of-view ray and draws its visible section. */
static void	draw_player_ray(t_minimap *minimap, double ray_angle)
{
	t_game			*game;
	double			ray_x;
	double			ray_y;
	double			step;
	t_minimap_point	point;

	game = minimap->game;
	ray_x = game->player.x;
	ray_y = game->player.y;
	step = 0.02;
	while (!collision(ray_x, ray_y, game))
	{
		minimap_map_to_screen(minimap, ray_x, ray_y, &point);
		if (point.x < MINIMAP_X || point.x >= MINIMAP_X + minimap->width
			|| point.y < MINIMAP_Y
			|| point.y >= MINIMAP_Y + minimap->height)
			break ;
		put_pixel(point.x, point.y, 0xFF0000, game);
		ray_x += sin(ray_angle * PI / 180.0) * step;
		ray_y -= cos(ray_angle * PI / 180.0) * step;
	}
}

/* Draws the player's field-of-view rays on the minimap. */
void	draw_player_rays(t_minimap *minimap)
{
	double	ray_direction;
	double	angle;
	int		i;

	ray_direction = minimap->game->player.direction;
	i = 0;
	while (i < minimap->game->screen_width)
	{
		angle = ray_direction - FOV / 2.0
			+ FOV * i / (minimap->game->screen_width - 1.0);
		draw_player_ray(minimap, angle);
		i++;
	}
}

/* Draws the player marker at its minimap position. */
void	draw_minimap_player(t_minimap *minimap)
{
	t_minimap_point	point;

	minimap_map_to_screen(minimap, minimap->game->player.x,
		minimap->game->player.y, &point);
	draw_square(minimap->game, (t_square){point.x - 5, point.y - 5,
		10, 0x00FF00});
}
