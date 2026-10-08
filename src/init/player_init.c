/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 15:13:01 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/08 15:13:03 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_player_start(char c)
{
	return (c == PLAYER_NORTH || c == PLAYER_SOUTH
		|| c == PLAYER_WEST || c == PLAYER_EAST);
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
		return (-1.0); // Invalid player start character
}

int	player_init(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.grid[i] != NULL)
	{
		j = 0;
		while (game->map.grid[i][j] != '\0')
		{
			if (is_player_start(game->map.grid[i][j]))
			{
				game->player.x = j + 0.5; // Center of the cell
				game->player.y = i + 0.5; // Center of the cell
				game->player.direction
					= get_player_direction(game->map.grid[i][j]);
				return (TRUE);
			}
			j++;
		}
		i++;
	}
	return (error_msg(NO_PLAYER_START));
}
