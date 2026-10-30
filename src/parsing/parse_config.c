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

static int	is_config_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\n');
}

static char	*dup_trimmed(char *str)
{
	char	*start;
	size_t	end;

	start = skip_config_whitespace(str);
	end = ft_strlen(start);
	while (end > 0 && is_config_whitespace(start[end - 1]))
		end--;
	return (ft_substr(start, 0, end));
}

static int	set_texture(char **texture, char *path, char *identifier,
		char *line)
{
	char	*texture_path;

	if (*texture != NULL)
		return (duplicate_config(identifier));
	texture_path = dup_trimmed(path);
	if (!texture_path)
		return (error_msg(MALLOC_ERROR));
	if (*texture_path == '\0')
	{
		free(texture_path);
		return (error_line(INVALID_LINE, line));
	}
	if (has_extension(texture_path, TEXTURE_EXTENSION) == false)
	{
		free(texture_path);
		return (error_msg(WRONG_TEXTURE_EXT));
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
	line = skip_config_whitespace(line);
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
