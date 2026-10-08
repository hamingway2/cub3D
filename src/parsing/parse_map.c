/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 15:14:02 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/08 15:14:04 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_line_length(char *line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (0);
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	return (i);
}

static char	*resize_line(char *line, int width)
{
	char	*new_line;
	int		len;
	int		i;

	len = get_line_length(line);
	new_line = malloc(sizeof(char) * (width + 1));
	if (!new_line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_line[i] = line[i];
		i++;
	}
	while (i < width)
	{
		new_line[i] = ' ';
		i++;
	}
	new_line[i] = '\0';
	free(line);
	return (new_line);
}

int	normalize_map(t_map *map)
{
	int		i;
	char	*new_line;

	i = 0;
	while (i < map->height)
	{
		new_line = resize_line(map->grid[i], map->width);
		if (!new_line)
			return (FALSE);
		map->grid[i] = new_line;
		i++;
	}
	return (TRUE);
}
