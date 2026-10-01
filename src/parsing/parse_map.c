#include "cub3d.h"

static int	get_map_height(char *filename)
{
	int		fd;
	int		height;
	int		map_started;
	char	*line;

	//load map from file
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error_msg(OPEN_ERROR));
	height = 0;
	map_started = FALSE;
	line = get_next_line(fd);
	while (line)
	{
		if (map_started == FALSE)
		{
			if (is_map_line(line))
				map_started = TRUE;
			else
			{
				free(line);
				line = get_next_line(fd);
				continue ;
			}
		}
		if (!is_empty_line(line)) //this check ensures that we don't count empty lines in the map height
			height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

static int read_map(t_game *game, char *filename)
{
	char	*line;
	int		i;
	int		width;
	int		fd;

	i = 0;
	line = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error_msg(OPEN_ERROR));	
	line = get_next_line(fd);
	while(is_map_line(line) == FALSE)
	{
		free(line);
		line = get_next_line(fd);
	}
	game->map.grid[i] = line;
	width = ft_strlen(line);
	i++;
	while (line)
	{
		line = get_next_line(fd);
		game->map.grid[i] = line;
		width = ft_max(width, (int)ft_strlen(line));
		i++;
	}
	game->map.grid[i] = NULL;
	return (width);
}

//ALLOCATION HAPPENS HERE!!!
int	parse_map(t_game *game, char *filename)
{
	int		height;
	int		width;

	height = get_map_height(filename);
	if (height <= 0)
		return (FALSE);
	game->map.grid = (char **)ft_calloc(height + 1, sizeof(char *));
	if (!game->map.grid)
		return (FALSE);
	width = read_map(game, filename);
	game->map.width = width;
	game->map.height = height;
	return (TRUE);
}
