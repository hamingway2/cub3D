#include "../../includes/cub3d.h"

int	is_empty_line(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (*line == '\0' || *line == '\n');
}

int	is_config_line(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (TRUE);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (TRUE);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (TRUE);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (TRUE);
	if (ft_strncmp(line, "F ", 2) == 0)
		return (TRUE);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (TRUE);
	return (FALSE);
}

int	is_map_line(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (*line == WALL || *line == EMPTY || *line == PLAYER_NORTH || *line == PLAYER_SOUTH
		|| *line == PLAYER_WEST || *line == PLAYER_EAST); // valid map lines start with a map character (might still be invalid)
}

int	parse_config(t_game *game, char *line)
{
	(void) game;
	(void) line;
	// Implementation for parsing configuration lines
	return (TRUE);
}

int	get_map_height(char *filename)
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

int read_map(t_game *game, int fd, char *first_line)
{
	char	*line;
	int		i;
	int		width;

	i = 0;
	game->map.grid[i] = first_line;
	width = ft_strlen(first_line);
	i++;
	line = get_next_line(fd);
	while (line)
	{
		game->map.grid[i] = line;
		width = ft_max(width, (int)ft_strlen(line));
		line = get_next_line(fd);
		i++;
	}
	game->map.grid[i] = NULL;
	return (width);
}

//ALLOCATION HAPPENS HERE!!!
int	load_map(t_game *game, int fd, char *first_line, char *filename)
{
	int		height;
	int		width;

	height = get_map_height(filename);
	if (height <= 0)
		return (FALSE);
	game->map.grid = ft_calloc(height + 1, sizeof(char *));
	if (!game->map.grid)
		return (FALSE);
	width = read_map(game, fd, first_line);
	game->map.width = width;
	game->map.height = height;
	return (TRUE);
}
