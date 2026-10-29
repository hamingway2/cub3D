/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_vector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 21:05:15 by azielnic          #+#    #+#             */
/*   Updated: 2026/10/29 19:00:00 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * Normalises diagonal movement to prevent the player from moving faster
 * when combining forward and sideways movement.
 */

static void	normalise_movement(double *move_x, double *move_y, int move_count)
{
	if (move_count > 1)
	{
		*move_x /= sqrt(2.0);
		*move_y /= sqrt(2.0);
	}
}

/*
 * Calculates the sideways movement vector based on the player's 
 * direction and the left or right movement keys.
 */

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

/*
 * Calculates the forward and backward movement vector based on the
 * player's direction and the corresponding movement keys.
 */

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

/*
 * Counts the number of active movement keys to determine whether
 * movement is requested and whether normalisation is needed.
 */

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

/*
 * Calculates the player's movement vector from the active movement keys, 
 * normalises diagonal movement and applies the movement speed scaled by 
 * the elapsed time between frames.
 */

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
