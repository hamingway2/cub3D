/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 17:21:58 by azielnic          #+#    #+#             */
/*   Updated: 2026/10/29 19:17:07 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * The init_ray functions initialise a ray for raycasting by calculating its 
 * direction and starting map cell, then setting the step directions and 
 * distances to the next grid boundaries along both axes. These values allow 
 * the DDA (Digital Differential Analysis) algorithm to traverse the map 
 * efficiently and detect walls.
 * 
 * HUGE_VAL is used when the ray does not move along an axis. For example, 
 * if the ray moves straight up, it does not move left or right, so it will 
 * never cross a vertical grid line. HUGE_VAL sets the distance for that axis 
 * to infinity, allowing the DDA algorithm to move along the axis where the 
 * ray actually travels.
 */

static void	init_ray_x(t_ray *ray, t_game *game)
{
	ray->delta_x = HUGE_VAL;
	if (ray->dir_x != 0.0)
		ray->delta_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_x < 0.0)
	{
		ray->step_x = -1;
		ray->side_x = (game->player.x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0 - game->player.x) * ray->delta_x;
	}
}

static void	init_ray_y(t_ray *ray, t_game *game)
{
	ray->delta_y = HUGE_VAL;
	if (ray->dir_y != 0.0)
		ray->delta_y = fabs(1.0 / ray->dir_y);
	if (ray->dir_y < 0.0)
	{
		ray->step_y = -1;
		ray->side_y = (game->player.y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0 - game->player.y) * ray->delta_y;
	}
}

void	init_ray(t_ray *ray, t_game *game, double ray_angle)
{
	ray->dir_x = sin(ray_angle * PI / 180.0);
	ray->dir_y = -cos(ray_angle * PI / 180.0);
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	ray->side = 0;
	init_ray_x(ray, game);
	init_ray_y(ray, game);
}
