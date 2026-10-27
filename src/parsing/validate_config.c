/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 20:15:49 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/27 20:15:51 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	has_missing_config(t_game *game)
{
	return (!game->texture_north || !game->texture_south
		|| !game->texture_west || !game->texture_east
		|| !game->floor_color_set || !game->ceiling_color_set);
}

static int	missing_config_error(t_game *game)
{
	error_msg(MISSING_CONFIG_LINES);
	if (!game->texture_north)
		ft_putstr_fd("NO\n", 2);
	if (!game->texture_south)
		ft_putstr_fd("SO\n", 2);
	if (!game->texture_west)
		ft_putstr_fd("WE\n", 2);
	if (!game->texture_east)
		ft_putstr_fd("EA\n", 2);
	if (!game->floor_color_set)
		ft_putstr_fd("F\n", 2);
	if (!game->ceiling_color_set)
		ft_putstr_fd("C\n", 2);
	return (FALSE);
}

int	validate_config(t_game *game)
{
	if (has_missing_config(game))
		return (missing_config_error(game));
	return (TRUE);
}
