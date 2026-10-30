/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 15:13:39 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/29 20:47:24 by azielnic         ###   ########.fr       */
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
	char	*texture_path;

	if (*texture != NULL)
		return (duplicate_config(identifier));
	while (*path == ' ' || *path == '\t')
		path++;
	if (*path == '\0' || *path == '\n')
		return (error_line(INVALID_LINE, line));
	texture_path = dup_without_newline(path);
	if (!texture_path)
		return (error_msg(MALLOC_ERROR));
	if (has_extension(texture_path, TEXTURE_EXTENSION) == false)
	{
		free(texture_path);
		return (error_msg(WRONG_TEXTURE_EXTENSION));
	}
	if (has_filename_before_extension(texture_path,
			TEXTURE_EXTENSION) == false)
	{
		free(texture_path);
		return (error_msg(INVALID_TEXTURE_FILE_NAME));
	}
	*texture = texture_path;
	return (true);
}

int	parse_texture(t_game *game, char *line)
{
	char	*original_line;

	original_line = line;
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strncmp(line, "NO", 2) == 0)
		return (set_texture(&game->north.path, line + 2, "NO",
				original_line));
	if (ft_strncmp(line, "SO", 2) == 0)
		return (set_texture(&game->south.path, line + 2, "SO",
				original_line));
	if (ft_strncmp(line, "WE", 2) == 0)
		return (set_texture(&game->west.path, line + 2, "WE",
				original_line));
	if (ft_strncmp(line, "EA", 2) == 0)
		return (set_texture(&game->east.path, line + 2, "EA",
				original_line));
	return (false);
}

int	parse_config(t_game *game, char *line)
{
	if (is_texture_line(line))
		return (parse_texture(game, line));
	else if (is_color_line(line))
		return (parse_color(game, line));
	else
		return (error_msg(INVALID_CONFIG_LINE_1 INVALID_CONFIG_LINE_2));
}
