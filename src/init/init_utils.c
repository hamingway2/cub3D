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
	return (*line == 'N' || *line == 'S'
		|| *line == 'E' || *line == 'W' || *line == 'F' || *line == 'C');
}

int	parse_config(t_game *game, char *line)
{
	// Implementation for parsing configuration lines
	return (TRUE);
}

void load_map(t_game *game, int fd, char *line)
{
	// Implementation for loading the map from the file
}
