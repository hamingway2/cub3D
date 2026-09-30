#include "cub3d.h"

int	is_empty_line(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (*line == '\0' || *line == '\n');
}

//int	is_texture_line(char *line);
//int	is_color_line(char *line);

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
