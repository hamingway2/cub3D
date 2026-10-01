#include "cub3d.h"

int	parse_file(t_game *game, char *filename)
{
	int		fd;
	char	*line;

	//load map from file
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error_msg(OPEN_ERROR));
	line = get_next_line(fd);
	while (line)
	{
		//skip empty lines
		if (is_empty_line(line))
			;
		//parse configuration lines
		else if (is_config_line(line))
			parse_config(game, line);
		//once the first map line is detected, load the map and break the loop, validate the map in load_map function
		else if (is_map_line(line))
		{
			free(line);
			close(fd);
			fd = -1; //set fd to -1 to avoid closing it again in the end of the function
			parse_map(game, filename);
			break ;
		}
		//if the line is neither empty, nor a configuration line, nor a map line, it's an invalid line
		else
		{
			free(line);
			close(fd);
			return (error_msg(INVALID_LINE));
		}
		free(line);
		line = get_next_line(fd);
	}
	if (fd >= 0)
		close(fd);
	return (TRUE);
}
