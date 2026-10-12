/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 15:13:39 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/12 16:54:47 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static char	*dup_without_newline(char *str)
// {
// 	size_t	len;

// 	len = ft_strlen(str);
// 	if (len > 0 && str[len - 1] == '\n')
// 		len--;
// 	return (ft_substr(str, 0, len));
// }

// static int	set_texture(char **texture, char *path)
// {
// 	if (*texture != NULL)
// 		return (error_msg(DUPLICATE_TEXTURE));
// 	*texture = dup_without_newline(path);
// 	return (TRUE);
// }

static int	set_color(int *color, char *value)
{
	int	r;
	int	g;
	int	b;

	if (*color != 0)
		return (error_msg(DUPLICATE_COLOR));
	r = ft_atoi(value);
	while (*value && *value != ',')
		value++;
	if (*value != ',')
		return (FALSE);
	value++;
	g = ft_atoi(value);
	while (*value && *value != ',')
		value++;
	if (*value != ',')
		return (FALSE);
	value++;
	b = ft_atoi(value);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (FALSE);
	*color = (r << 16) | (g << 8) | b;
	return (TRUE);
}

// int	parse_texture(t_game *game, char *line)
// {
// 	if (ft_strncmp(line, "NO ", 3) == 0)
// 		return (set_texture(&game->north.path, line + 3));
// 	if (ft_strncmp(line, "SO ", 3) == 0)
// 		return (set_texture(&game->south.path, line + 3));
// 	if (ft_strncmp(line, "WE ", 3) == 0)
// 		return (set_texture(&game->west.path, line + 3));
// 	if (ft_strncmp(line, "EA ", 3) == 0)
// 		return (set_texture(&game->east.path, line + 3));
// 	return (FALSE);
// }

// FOR TEXTURE TESTING
int	parse_texture(t_game *game, char *line)
{
	(void)line;
	if (!game->north.path)
		game->north.path = ft_strdup("./texture/wolfenstein_north.xpm");
	if (!game->south.path)
		game->south.path = ft_strdup("./texture/wolfenstein_south.xpm");
	if (!game->west.path)
		game->west.path = ft_strdup("./texture/wolfenstein_west.xpm");
	if (!game->east.path)
		game->east.path = ft_strdup("./texture/wolfenstein_east.xpm");
	if (!game->north.path || !game->south.path
		|| !game->west.path || !game->east.path)
		return (error_msg(MALLOC_ERROR));
	return (TRUE);
}

int	parse_color(t_game *game, char *line)
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
