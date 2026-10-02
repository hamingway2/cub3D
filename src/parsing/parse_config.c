#include "cub3d.h"

int parse_texture(t_game *game, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		game->texture_north = ft_strdup(line + 3);
		return (TRUE);
	}
	if (ft_strncmp(line, "SO ", 3) == 0)
	{
		game->texture_south = ft_strdup(line + 3);
		return (TRUE);
	}
	if (ft_strncmp(line, "WE ", 3) == 0)
	{
		game->texture_west = ft_strdup(line + 3);
		return (TRUE);
	}
	if (ft_strncmp(line, "EA ", 3) == 0)
	{
		game->texture_east = ft_strdup(line + 3);
		return (TRUE);
	}
	return (FALSE);
}

int parse_color(t_game *game, char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		game->floor_color = ft_strdup(line + 2);
		return (TRUE);
	}
	if (ft_strncmp(line, "C ", 2) == 0)
	{
		game->ceiling_color = ft_strdup(line + 2);
		return (TRUE);
	}
	return (FALSE);
}

int	parse_config(t_game *game, char *line)
{
	if (is_texture_line(line))
		return (parse_texture(game, line));
	else if (is_color_line(line))
		return (parse_color(game, line));
	else
		return (error_msg(INVALID_CONFIG_LINE));
}
