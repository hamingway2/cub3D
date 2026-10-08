#include "cub3d.h"

static int	add_map_line(t_game *game, char *line, int *map_height, int *capacity)
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

int	parse_file(t_game *game, char *filename)
{
	int		fd;
	int		map_started;
	int		map_height;
	int		capacity;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error_msg(OPEN_ERROR));

	map_started = FALSE;
	map_height = 0;
	capacity = 8;

	game->map.grid = ft_calloc(capacity + 1, sizeof(char *));
	if (!game->map.grid)
	{
		close(fd);
		return (FALSE);
	}

	line = get_next_line(fd);
	while (line)
	{
		if (!map_started)
		{
			/* Ignore empty lines before the map */
			if (is_empty_line(line))
			{
				free(line);
				line = get_next_line(fd);
				continue;
			}

			/* Parse configuration */
			if (is_config_line(line))
			{
				if (parse_config(game, line) == FALSE)
				{
					free(line);
					close(fd);
					return (FALSE);
				}
			}
			/* First map line */
			else if (is_map_line(line))
			{
				map_started = TRUE;

				if (!add_map_line(game, line, &map_height, &capacity))
				{
					free(line);
					close(fd);
					return (FALSE);
				}
			}
			else
			{
				free(line);
				close(fd);
				return (error_msg(INVALID_LINE));
			}
		}
		else
		{
			/*
			 * Once the map has started, every subsequent
			 * line must be a map line.
			 */
			if (is_map_line(line))
			{
				if (!add_map_line(game, line, &map_height, &capacity))
				{
					free(line);
					close(fd);
					return (FALSE);
				}
			}
			else if (!is_empty_line(line))
			{
				/*
				 * Non-map content after the map has started
				 * is invalid.
				 */
				free(line);
				close(fd);
				return (error_msg(INVALID_LINE));
			}
		}

		free(line);
		line = get_next_line(fd);
	}

	close(fd);

	if (!map_started || map_height == 0)
		return (error_msg(INVALID_MAP));

	game->map.height = map_height;
	game->map.width = 0;

	/*
	 * Find the maximum row width.
	 */
	for (int i = 0; i < map_height; i++)
	{
		int	len;

		len = ft_strlen(game->map.grid[i]);
		if (len > game->map.width)
			game->map.width = len;
	}
	if (!normalize_map(&game->map))
		return (error_msg(MALLOC_ERROR));
	return (validate_map(game));
}
