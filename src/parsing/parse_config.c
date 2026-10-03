#include "cub3d.h"

static int set_texture(char **texture, char *path)
{
    if (*texture != NULL)
        return (error_msg(DUPLICATE_TEXTURE));
    *texture = ft_strdup(path);
    return (TRUE);
}

static int set_color(char **color, char *value)
{
    if (*color != NULL)
        return (error_msg(DUPLICATE_COLOR));
    *color = ft_strdup(value);
    return (TRUE);
}

int parse_texture(t_game *game, char *line)
{
    if (ft_strncmp(line, "NO ", 3) == 0)
        return (set_texture(&game->texture_north, line + 3));
    if (ft_strncmp(line, "SO ", 3) == 0)
        return (set_texture(&game->texture_south, line + 3));
    if (ft_strncmp(line, "WE ", 3) == 0)
        return (set_texture(&game->texture_west, line + 3));
    if (ft_strncmp(line, "EA ", 3) == 0)
        return (set_texture(&game->texture_east, line + 3));
    return (FALSE);
}

int parse_color(t_game *game, char *line)
{
    if (ft_strncmp(line, "F ", 2) == 0)
        return (set_color(&game->floor_color, line + 2));
    if (ft_strncmp(line, "C ", 2) == 0)
        return (set_color(&game->ceiling_color, line + 2));
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
