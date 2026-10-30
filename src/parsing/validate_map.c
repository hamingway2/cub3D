/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 15:14:24 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/29 18:11:25 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_map_character(char c)
{
	return (c == WALKABLE_TILE || c == WALL || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ');
}

static int	map_character_error(int row, int column)
{
	ft_putstr_fd(ERROR, 2);
	ft_putstr_fd(INVALID_MAP_CHARACTER, 2);
	ft_putnbr_fd(row + 1, 2);
	ft_putstr_fd(INVALID_MAP_COLUMN, 2);
	ft_putnbr_fd(column + 1, 2);
	ft_putchar_fd('\n', 2);
	return (false);
}

static int	validate_map_character_row(char *row, int row_index,
		int *player_count)
{
	int	column;

	column = 0;
	while (row[column])
	{
		if (!is_valid_map_character(row[column]))
		{
			map_character_error(row_index, column);
			return (false);
		}
		if (is_player_char(row[column]))
		{
			(*player_count)++;
			if (*player_count > 1)
				return (error_msg(MULTIPLE_PLAYER_STARTS));
		}
		column++;
	}
	return (true);
}

static int	validate_map_characters(t_game *game)
{
	int	row;
	int	player_count;

	row = 0;
	player_count = 0;
	while (game->map.grid[row])
	{
		if (!validate_map_character_row(game->map.grid[row], row,
				&player_count))
			return (false);
		row++;
	}
	return (true);
}

int	validate_map(t_game *game)
{
	if (validate_map_walls(game) == false)
	{
		return (false);
	}
	if (validate_map_characters(game) == false)
	{
		return (false);
	}
	return (true);
}
