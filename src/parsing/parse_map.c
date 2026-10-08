#include "cub3d.h"

static int	get_map_height(char *filename)
{
	int		fd;
	int		height;
	char	*line;

	get_next_line(-1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error_msg(OPEN_ERROR));
	height = 0;
	line = get_next_line(fd);
	printf("%s\n", line);
	/* Skip everything before the map */
	while (line && !is_map_line(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	/* Count map lines */
	
	while (line && is_map_line(line))
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
	return (height);
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

static int	read_map(t_game *game, char *filename)
{
	char	*line;
	int		i;
	int		width;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error_msg(OPEN_ERROR));

	i = 0;
	width = 0;
	line = get_next_line(fd);

	/* Skip everything before the map */
	while (line && !is_map_line(line))
	{
		free(line);
		line = get_next_line(fd);
	}

	/* Read map lines */
	while (line && is_map_line(line))
	{
		game->map.grid[i] = line;
		if (get_line_length(line) > width)
			width = get_line_length(line);
		i++;
		line = get_next_line(fd);
	}
	game->map.grid[i] = NULL;
	if (line)
		free(line);
	close(fd);
	/* Make every row the same width */
	i = 0;
	while (game->map.grid[i])
	{
		game->map.grid[i] = resize_line(game->map.grid[i], width);
		if (!game->map.grid[i])
			return (-1);
		i++;
	}
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
	if (width < 0)
		return (FALSE);
	printf("height = %d\n", height);
	printf("rows read:\n");
	int i = 0;
	while (game->map.grid[i])
	{
		printf("[%d] = %p \"%s\"\n",
		i, (void *)game->map.grid[i], game->map.grid[i]);
		i++;
	}
	printf("actual rows = %d\n", i);
	game->map.width = width;
	game->map.height = height;
//	game->map.height = get_real_map_height(&game->map);
	return (validate_map(game));
}
