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
/*
static char	*find_map_start(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && !is_map_line(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

static int	count_map_lines(int fd, char *line)
{
	int	height;

	height = 0;
	while (line && is_map_line(line))
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (height);
}

static int	get_map_height(char *filename)
{
	int		fd;
	int		height;
	char	*line;

	get_next_line(-1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error_msg(OPEN_ERROR));
	line = find_map_start(fd);
	height = count_map_lines(fd, line);
	close(fd);
	return (height);
}*/

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
