/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_vector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 21:05:15 by azielnic          #+#    #+#             */
/*   Updated: 2026/10/12 21:10:01 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	normalise_movement(double *move_x, double *move_y, int move_count)
{
	if (move_count > 1)
	{
		*move_x /= sqrt(2.0);
		*move_y /= sqrt(2.0);
	}
}

static void	get_strafe_movement(t_player *player, double *move_x,
		double *move_y)
{
	double	angle;

	angle = player->direction * PI / 180.0;
	if (player->key_left)
	{
		*move_x -= cos(angle);
		*move_y -= sin(angle);
	}
	if (player->key_right)
	{
		*move_x += cos(angle);
		*move_y += sin(angle);
	}
}

static void	get_forward_movement(t_player *player, double *move_x,
		double *move_y)
{
	double	angle;

	angle = player->direction * PI / 180.0;
	if (player->key_up)
	{
		*move_x += sin(angle);
		*move_y -= cos(angle);
	}
	if (player->key_down)
	{
		*move_x -= sin(angle);
		*move_y += cos(angle);
	}
}

static int	get_move_count(t_player *player)
{
	int	count;

	count = 0;
	if (player->key_up)
		count++;
	if (player->key_down)
		count++;
	if (player->key_left)
		count++;
	if (player->key_right)
		count++;
	return (count);
}

void	get_movement_vector(t_player *player, double delta_time,
		double *move_x, double *move_y)
{
	int	move_count;

	*move_x = 0.0;
	*move_y = 0.0;
	move_count = get_move_count(player);
	if (move_count == 0)
		return ;
	get_forward_movement(player, move_x, move_y);
	get_strafe_movement(player, move_x, move_y);
	normalise_movement(move_x, move_y, move_count);
	*move_x *= PLAYER_SPEED * delta_time;
	*move_y *= PLAYER_SPEED * delta_time;
}
