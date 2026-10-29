/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 16:16:24 by azielnic          #+#    #+#             */
/*   Updated: 2026/10/12 16:27:20 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_texture(t_game *game, t_texture *texture, char *path)
{
	texture->img.img = mlx_xpm_file_to_image(game->mlx, path, &texture->width,
			&texture->height);
	if (!texture->img.img)
		return (error_msg("Failed to load texture\n"));
	texture->img.addr = mlx_get_data_addr(texture->img.img,
			&texture->img.bits_per_pixel,
			&texture->img.line_length,
			&texture->img.endian);
	if (!texture->img.addr)
		return (error_msg("Failed to get texture data\n"));
	return (true);
}

int	load_all_textures(t_game *game)
{
	if (!game->north.path || !game->south.path
		|| !game->west.path || !game->east.path)
		return (error_msg("Missing texture path\n"));
	if (!load_texture(game, &game->north, game->north.path))
		return (false);
	if (!load_texture(game, &game->south, game->south.path))
		return (false);
	if (!load_texture(game, &game->west, game->west.path))
		return (false);
	if (!load_texture(game, &game->east, game->east.path))
		return (false);
	return (true);
}
