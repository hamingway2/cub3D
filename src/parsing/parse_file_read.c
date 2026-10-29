/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_read.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 20:15:27 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/29 18:11:25 by azielnic         ###   ########.fr       */
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
			return (false);
		ft_memcpy(new_grid, game->map.grid,
			(*map_height) * sizeof(char *));
		free(game->map.grid);
		game->map.grid = new_grid;
	}
	game->map.grid[*map_height] = ft_strdup(line);
	if (!game->map.grid[*map_height])
		return (false);
	(*map_height)++;
	return (true);
}

static int	process_before_map(t_game *game, char *line, t_parse *parse)
{
	if (is_empty_line(line))
		return (true);
	if (is_config_line(line))
		return (parse_config(game, line));
	if (is_map_line(line))
	{
		parse->map_started = true;
		return (add_map_line(game, line, &parse->map_height, &parse->capacity));
	}
	return (error_line(INVALID_LINE, line));
}

static int	process_after_map(t_game *game, char *line, t_parse *parse)
{
	if (is_config_line(line))
		return (error_msg(CONFIG_AFTER_MAP));
	if (is_empty_line(line))
		return (error_line(INVALID_LINE, line));
	return (add_map_line(game, line, &parse->map_height, &parse->capacity));
}

int	read_map_file(t_game *game, int fd, t_parse *parse)
{
	char	*line;
	int		result;
	int		read_error;

	line = get_next_line(fd, &read_error);
	if (read_error)
		return (error_msg(FILE_READ_ERROR));
	if (!line)
		return (error_msg(EMPTY_FILE));
	while (line)
	{
		if (!parse->map_started)
			result = process_before_map(game, line, parse);
		else
			result = process_after_map(game, line, parse);
		free(line);
		if (!result)
			return (false);
		line = get_next_line(fd, &read_error);
		if (read_error)
			return (error_msg(FILE_READ_ERROR));
	}
	if (!parse->map_started || parse->map_height == 0)
		return (error_msg(INVALID_MAP));
	return (true);
}
