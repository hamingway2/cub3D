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

static int	duplicate_config(char *identifier)
{
	ft_putstr_fd(ERROR, 2);
	ft_putstr_fd("Duplicate config line: ", 2);
	ft_putstr_fd(identifier, 2);
	ft_putchar_fd('\n', 2);
	return (FALSE);
}

static int	set_texture(char **texture, char *path, char *identifier)
{
	if (*texture != NULL)
		return (duplicate_config(identifier));
	*texture = dup_without_newline(path);
	return (TRUE);
}

static int	is_color_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\n');
}

static int	parse_color_component(char **value, int *component,
		char separator)
{
	int	result;
	int	digits;

	while (is_color_space(**value))
		(*value)++;
	result = 0;
	digits = 0;
	while (**value >= '0' && **value <= '9')
	{
		result = result * 10 + (**value - '0');
		if (result > 255)
			return (FALSE);
		(*value)++;
		digits++;
	}
	while (is_color_space(**value))
		(*value)++;
	if (digits == 0 || **value != separator)
		return (FALSE);
	if (separator != '\0')
		(*value)++;
	else if (**value != '\0')
		return (FALSE);
	*component = result;
	return (TRUE);
}

static int	set_color(int *color, bool *color_set, char *value,
		char *identifier)
{
	int	r;
	int	g;
	int	b;

	if (*color_set)
		return (duplicate_config(identifier));
	if (!parse_color_component(&value, &r, ',')
		|| !parse_color_component(&value, &g, ',')
		|| !parse_color_component(&value, &b, '\0'))
		return (error_msg(INVALID_COLOR_VALUE));
	*color = (r << 16) | (g << 8) | b;
	*color_set = TRUE;
	return (TRUE);
}

int	parse_texture(t_game *game, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (set_texture(&game->texture_north, line + 3, "NO"));
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (set_texture(&game->texture_south, line + 3, "SO"));
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (set_texture(&game->texture_west, line + 3, "WE"));
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (set_texture(&game->texture_east, line + 3, "EA"));
	return (FALSE);
}

int	parse_color(t_game *game, char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strncmp(line, "F ", 2) == 0)
		return (set_color(&game->floor_color, &game->floor_color_set,
				line + 2, "F"));
	if (ft_strncmp(line, "C ", 2) == 0)
		return (set_color(&game->ceiling_color, &game->ceiling_color_set,
				line + 2, "C"));
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
