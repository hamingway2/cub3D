/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 20:53:18 by azielnic          #+#    #+#             */
/*   Updated: 2026/10/29 20:56:28 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_keys(t_player *player)
{
	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;
	player->key_turn_left = false;
	player->key_turn_right = false;
}

static double	get_player_direction(char player_start)
{
	if (player_start == PLAYER_NORTH)
		return (0.0);
	else if (player_start == PLAYER_EAST)
		return (90.0);
	else if (player_start == PLAYER_SOUTH)
		return (180.0);
	else if (player_start == PLAYER_WEST)
		return (270.0);
	else
		return (-1.0);
}

/*
 * Initialises the camera plane based on the player's viewing direction and 
 * the field of view (FOV). Calculates the plane's length using the half-FOV 
 * angle and sets its x and y components perpendicular to the viewing 
 * direction for use in raycasting.
 */

static void	init_player_plane(t_player *player)
{
	double	angle;
	double	plane_length;

	angle = player->direction * PI / 180;
	plane_length = tan((FOV / 2.0) * PI / 180.0);
	player->plane_x = cos(angle) * plane_length;
	player->plane_y = -sin(angle) * plane_length;
}

/*
 * Initialises the player's keys and searches the map for the player's
 * starting position. Sets the player's coordinates to the center of the 
 * corresponding map cell, determines the initial viewing direction and 
 * initialises the camera plane. Returns true on success or displays an 
 * error message if no player starting position is found.
 */

int	player_init(t_game *game)
{
	int	i;
	int	j;

	init_keys(&game->player);
	i = 0;
	while (game->map.grid[i] != NULL)
	{
		j = 0;
		while (game->map.grid[i][j] != '\0')
		{
			if (is_player_char(game->map.grid[i][j]))
			{
				game->player.x = j + 0.5;
				game->player.y = i + 0.5;
				game->player.direction
					= get_player_direction(game->map.grid[i][j]);
				init_player_plane(&game->player);
				return (true);
			}
			j++;
		}
		i++;
	}
	return (error_msg(NO_PLAYER_START));
}
