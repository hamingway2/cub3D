/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 17:20:11 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/08 17:20:13 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_config_separator(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\0');
}

int	is_texture_line(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strncmp(line, "NO", 2) == 0 && is_config_separator(line[2]))
		return (TRUE);
	if (ft_strncmp(line, "SO", 2) == 0 && is_config_separator(line[2]))
		return (TRUE);
	if (ft_strncmp(line, "WE", 2) == 0 && is_config_separator(line[2]))
		return (TRUE);
	if (ft_strncmp(line, "EA", 2) == 0 && is_config_separator(line[2]))
		return (TRUE);
	return (FALSE);
}

int	is_color_line(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strncmp(line, "F", 1) == 0 && is_config_separator(line[1]))
		return (TRUE);
	if (ft_strncmp(line, "C", 1) == 0 && is_config_separator(line[1]))
		return (TRUE);
	return (FALSE);
}

int	is_config_line(char *line)
{
	return (is_texture_line(line) || is_color_line(line));
}
