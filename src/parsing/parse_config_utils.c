/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 17:20:11 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/29 18:11:25 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*skip_config_whitespace(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

static int	is_config_separator(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\0');
}

int	duplicate_config(char *identifier)
{
	error_msg(DUPLICATE_CONFIG_LINE);
	ft_putstr_fd(identifier, 2);
	ft_putchar_fd('\n', 2);
	return (false);
}

int	is_texture_line(char *line)
{
	line = skip_config_whitespace(line);
	if (ft_strncmp(line, "NO", 2) == 0 && is_config_separator(line[2]))
		return (true);
	if (ft_strncmp(line, "SO", 2) == 0 && is_config_separator(line[2]))
		return (true);
	if (ft_strncmp(line, "WE", 2) == 0 && is_config_separator(line[2]))
		return (true);
	if (ft_strncmp(line, "EA", 2) == 0 && is_config_separator(line[2]))
		return (true);
	return (false);
}

int	is_color_line(char *line)
{
	line = skip_config_whitespace(line);
	if (ft_strncmp(line, "F", 1) == 0 && is_config_separator(line[1]))
		return (true);
	if (ft_strncmp(line, "C", 1) == 0 && is_config_separator(line[1]))
		return (true);
	return (false);
}
