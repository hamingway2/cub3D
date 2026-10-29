/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 17:21:58 by azielnic          #+#    #+#             */
/*   Updated: 2026/10/12 18:36:07 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
