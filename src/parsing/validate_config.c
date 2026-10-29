/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 20:15:49 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/29 18:11:25 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	has_missing_config(t_game *game)
{
	return (!game->north.path || !game->south.path
		|| !game->west.path || !game->east.path
		|| !game->floor_color_set || !game->ceiling_color_set);
}

static int	missing_config_error(t_game *game)
{
	error_msg(MISSING_CONFIG_LINES);
	if (!game->north.path)
		ft_putstr_fd("NO\n", 2);
	if (!game->south.path)
		ft_putstr_fd("SO\n", 2);
	if (!game->west.path)
		ft_putstr_fd("WE\n", 2);
	if (!game->east.path)
		ft_putstr_fd("EA\n", 2);
	if (!game->floor_color_set)
		ft_putstr_fd("F\n", 2);
	if (!game->ceiling_color_set)
		ft_putstr_fd("C\n", 2);
	return (false);
}

int	validate_config(t_game *game)
{
	if (has_missing_config(game))
		return (missing_config_error(game));
	return (true);
}
