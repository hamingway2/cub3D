/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 17:51:45 by azielnic          #+#    #+#             */
/*   Updated: 2026/10/12 21:05:50 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <sys/time.h>

static bool	is_wall_cell(t_game *game, int map_x, int map_y)
{
	if (map_x < 0 || map_y < 0 || map_x >= game->map.width
		|| map_y >= game->map.height)
		return (true);
	return (game->map.grid[map_y][map_x] == WALL);
}

bool	collision(double x, double y, t_game *game)
{
	int	map_x;
	int	map_y;

	map_x = (int)floor(x - PLAYER_RADIUS);
	map_y = (int)floor(y - PLAYER_RADIUS);
	if (is_wall_cell(game, map_x, map_y))
		return (true);
	map_x = (int)floor(x + PLAYER_RADIUS);
	if (is_wall_cell(game, map_x, map_y))
		return (true);
	map_y = (int)floor(y + PLAYER_RADIUS);
	if (is_wall_cell(game, map_x, map_y))
		return (true);
	map_x = (int)floor(x - PLAYER_RADIUS);
	if (is_wall_cell(game, map_x, map_y))
		return (true);
	return (false);
}

void	rotate_player(t_player *player, double delta_time)
{
	double	rotation;

	if (player->key_turn_left == player->key_turn_right)
		return ;
	rotation = TURN_SPEED * delta_time;
	if (player->key_turn_left)
		rotation = -rotation;
	player->direction += rotation;
	while (player->direction < 0.0)
		player->direction += 360.0;
	while (player->direction >= 360.0)
		player->direction -= 360.0;
}

void	move_player(t_player *player, t_game *game, double delta_time)
{
	double	move_x;
	double	move_y;

	if (delta_time < 0.0)
		delta_time = 0.0;
	if (delta_time > 0.1)
		delta_time = 0.1;
	get_movement_vector(player, delta_time, &move_x, &move_y);
	if (!collision(player->x + move_x, player->y, game))
		player->x += move_x;
	if (!collision(player->x, player->y + move_y, game))
		player->y += move_y;
}
