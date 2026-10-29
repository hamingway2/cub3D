/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 15:13:39 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/08 15:13:41 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*dup_without_newline(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		len--;
	return (ft_substr(str, 0, len));
}

static int	set_texture(char **texture, char *path, char *identifier,
		char *line)
{
	if (*texture != NULL)
		return (duplicate_config(identifier));
	while (*path == ' ' || *path == '\t')
		path++;
	if (*path == '\0' || *path == '\n')
		return (error_line(INVALID_LINE, line));
	*texture = dup_without_newline(path);
	if (!*texture)
		return (error_msg(MALLOC_ERROR));
	return (TRUE);
}

int	parse_texture(t_game *game, char *line)
{
	char	*original_line;

	original_line = line;
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strncmp(line, "NO", 2) == 0)
		return (set_texture(&game->texture_north, line + 2, "NO",
				original_line));
	if (ft_strncmp(line, "SO", 2) == 0)
		return (set_texture(&game->texture_south, line + 2, "SO",
				original_line));
	if (ft_strncmp(line, "WE", 2) == 0)
		return (set_texture(&game->texture_west, line + 2, "WE",
				original_line));
	if (ft_strncmp(line, "EA", 2) == 0)
		return (set_texture(&game->texture_east, line + 2, "EA",
				original_line));
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
