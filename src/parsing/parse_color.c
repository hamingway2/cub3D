/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 20:15:12 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/29 18:11:25 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		if (result > (255 - (**value - '0')) / 10)
			return (false);
		result = result * 10 + (**value - '0');
		(*value)++;
		digits++;
	}
	while (is_color_space(**value))
		(*value)++;
	if (digits == 0 || **value != separator)
		return (false);
	if (separator != '\0')
		(*value)++;
	else if (**value != '\0')
		return (false);
	*component = result;
	return (true);
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
	*color_set = true;
	return (true);
}

int	parse_color(t_game *game, char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strncmp(line, "F", 1) == 0)
		return (set_color(&game->floor_color, &game->floor_color_set,
				line + 1, "F"));
	if (ft_strncmp(line, "C", 1) == 0)
		return (set_color(&game->ceiling_color, &game->ceiling_color_set,
				line + 1, "C"));
	return (false);
}
