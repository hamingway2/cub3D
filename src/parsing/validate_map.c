/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 15:14:24 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/08 15:14:26 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_map_character(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
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
	return (FALSE);
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
			return (FALSE);
		}
		if (is_player_char(row[column]))
		{
			(*player_count)++;
			if (*player_count > 1)
				return (error_msg(MULTIPLE_PLAYER_STARTS));
		}
		column++;
	}
	return (TRUE);
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
			return (FALSE);
		row++;
	}
	return (TRUE);
}

int	validate_map(t_game *game)
{
	if (validate_map_walls(game) == FALSE)
	{
		return (FALSE);
	}
	if (validate_map_characters(game) == FALSE)
	{
		return (FALSE);
	}
	return (TRUE);
}
