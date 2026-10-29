/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 16:49:07 by azielnic          #+#    #+#             */
/*   Updated: 2026/10/12 18:34:47 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	step_ray(t_ray *ray)
{
	if (ray->side_x < ray->side_y)
	{
		ray->side_x += ray->delta_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_y += ray->delta_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

static void	cast_ray(t_ray *ray, t_game *game)
{
	while (ray->map_x >= 0 && ray->map_y >= 0
		&& ray->map_x < game->map.width && ray->map_y < game->map.height
		&& game->map.grid[ray->map_y][ray->map_x] != WALL)
		step_ray(ray);
	if (ray->side == 0)
		ray->perp_dist = ray->side_x - ray->delta_x;
	else
		ray->perp_dist = ray->side_y - ray->delta_y;
	if (ray->perp_dist < 0.001)
		ray->perp_dist = 0.001;
}

static void	draw_walls(t_game *game, double ray_angle, int screen_x)
{
	t_ray	ray;

	init_ray(&ray, game, ray_angle);
	cast_ray(&ray, game);
	draw_textured_column(game, &ray, screen_x);
}

void	draw_raycasting(t_game *game)
{
	double	ray_angle;
	int		x;

	x = 0;
	while (x < game->screen_width)
	{
		ray_angle = game->player.direction - FOV / 2.0
			+ FOV * x / (game->screen_width - 1.0);
		draw_walls(game, ray_angle, x);
		x++;
	}
}
