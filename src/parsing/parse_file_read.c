/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_read.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 20:15:27 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/27 20:15:29 by gkhavari         ###   ########.fr       */
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

	line = get_next_line(fd);
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
			return (FALSE);
		line = get_next_line(fd);
	}
	if (!parse->map_started || parse->map_height == 0)
		return (error_msg(INVALID_MAP));
	return (TRUE);
}
