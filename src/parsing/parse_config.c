#include "cub3d.h"

//int	parse_texture(t_game *game, char *line);
//int	parse_color(t_game *game, char *line);
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

int	parse_config(t_game *game, char *line)
{
	(void) game;
	(void) line;
	// Implementation for parsing configuration lines
	return (TRUE);
}
