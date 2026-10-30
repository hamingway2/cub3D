/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 15:21:58 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/29 18:11:25 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_empty_line(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (*line == '\0' || *line == '\n');
}

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_map_character(char c)
{
	return (c == ' ' || c == WALKABLE_TILE || c == WALL
		|| is_player_char(c));
}

int	is_map_line(char *line)
{
	int	i;

	if (!line)
		return (false);
	if (is_empty_line(line))
		return (false);
	if (is_config_line(line))
		return (false);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!is_map_character(line[i]))
			return (false);
		i++;
	}
	if (line[i] == '\n' && line[i + 1] != '\0')
		return (false);
	return (true);
}
