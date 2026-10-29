/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 15:21:25 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/08 15:21:27 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_map_width(t_game *game, int map_height)
{
	int	i;
	int	len;

	game->map.width = 0;
	i = 0;
	while (i < map_height)
	{
		len = get_line_length(game->map.grid[i]);
		if (len > game->map.width)
			game->map.width = len;
		i++;
	}
}

static int	finish_map(t_game *game, int map_height)
{
	game->map.height = map_height;
	get_map_width(game, map_height);
	if (!normalize_map(&game->map))
		return (error_msg(MALLOC_ERROR));
	return (validate_map(game));
}

int	parse_file(t_game *game, char *filename)
{
	int		fd;
	t_parse	parse;

	parse.map_started = FALSE;
	parse.map_height = 0;
	parse.capacity = 8;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error_msg(OPEN_ERROR));
	game->map.grid = ft_calloc(parse.capacity + 1, sizeof(char *));
	if (!game->map.grid)
	{
		close(fd);
		return (error_msg(MALLOC_ERROR));
	}
	if (!read_map_file(game, fd, &parse))
	{
		close(fd);
		return (FALSE);
	}
	close(fd);
	if (!validate_config(game))
		return (FALSE);
	return (finish_map(game, parse.map_height));
}
