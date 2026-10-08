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

static int	add_map_line(t_game *game, char *line,
	int *map_height, int *capacity)
{
	char	**new_grid;

	if (*map_height >= *capacity)
	{
		*capacity *= 2;
		new_grid = ft_calloc(*capacity + 1, sizeof(char *));
		if (!new_grid)
			return (FALSE);
		ft_memcpy(new_grid, game->map.grid,
			(*map_height) * sizeof(char *));
		free(game->map.grid);
		game->map.grid = new_grid;
	}
	game->map.grid[*map_height] = ft_strdup(line);
	if (!game->map.grid[*map_height])
		return (FALSE);
	(*map_height)++;
	return (TRUE);
}

/*Opens file and allocates the initial map grid*/
static int	init_map_file(t_game *game, char *filename,
				int *fd, int capacity)
{
	*fd = open(filename, O_RDONLY);
	if (*fd < 0)
		return (error_msg(OPEN_ERROR));
	game->map.grid = ft_calloc(capacity + 1, sizeof(char *));
	if (!game->map.grid)
	{
		close(*fd);
		return (FALSE);
	}
	return (TRUE);
}

static int	process_before_map(t_game *game, char *line, t_parse *parse)
{
	if (is_empty_line(line))
		return (TRUE);
	if (is_config_line(line))
		return (parse_config(game, line));
	if (is_map_line(line))
	{
		parse->map_started = TRUE;
		return (add_map_line(game, line, &parse->map_height, &parse->capacity));
	}
	return (error_msg(INVALID_LINE));
}

static int	process_after_map(t_game *game, char *line, t_parse *parse)
{
	if (is_map_line(line))
		return (add_map_line(game, line, &parse->map_height, &parse->capacity));
	if (!is_empty_line(line))
		return (error_msg(INVALID_LINE));
	return (TRUE);
}

/*Responsible only for deciding which state we're in*/
static int	process_line(t_game *game, char *line, t_parse *parse)
{
	if (!parse->map_started)
		return (process_before_map(game, line, parse));
	return (process_after_map(game, line, parse));
}

/*Reads lines, passes each line to the appropriate processor
detects an empty/invalid line*/
static int	read_map_file(t_game *game, int fd, t_parse *parse)
{
	char	*line;
	int		result;

	line = get_next_line(fd);
	while (line)
	{
		result = process_line(game, line, parse);
		free(line);
		if (!result)
			return (FALSE);
		line = get_next_line(fd);
	}
	if (!parse->map_started || parse->map_height == 0)
		return (error_msg(INVALID_MAP));
	return (TRUE);
}

static void	get_map_width(t_game *game, int map_height)
{
	int	i;
	int	len;

	game->map.width = 0;
	i = 0;
	while (i < map_height)
	{
		len = ft_strlen(game->map.grid[i]);
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
	if (!init_map_file(game, filename, &fd, parse.capacity))
		return (FALSE);
	if (!read_map_file(game, fd, &parse))
	{
		close(fd);
		return (FALSE);
	}
	close(fd);
	return (finish_map(game, parse.map_height));
}
