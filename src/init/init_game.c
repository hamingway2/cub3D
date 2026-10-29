/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 20:17:53 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/29 20:56:21 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * Initialises MiniLibX, retrieves the screen dimensions and creates the 
 * window and image used for rendering. Retrieves the image's pixel data 
 * address and its format information. Returns true on success or displays 
 * an error message and returns false if any step fails.
 */

int	game_init(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (error_msg("MiniLibX initialization failed\n"));
	mlx_get_screen_size(game->mlx, &game->screen_width,
		&game->screen_height);
	if (game->screen_width < 2 || game->screen_height < 1)
		return (error_msg("Could not determine screen dimensions\n"));
	game->window = mlx_new_window(game->mlx, game->screen_width,
			game->screen_height, "cub3d");
	if (!game->window)
		return (error_msg("Could not create MiniLibX window\n"));
	game->img.img = mlx_new_image(game->mlx, game->screen_width,
			game->screen_height);
	if (!game->img.img)
		return (error_msg("Could not create MiniLibX image\n"));
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	if (!game->img.addr)
		return (error_msg("Could not access MiniLibX image data\n"));
	return (true);
}

int	game_setup(t_game *game, char *file)
{
	ft_bzero(game, sizeof(*game));
	if (parse_file(game, file) == false)
		return (false);
	if (player_init(game) == false)
		return (false);
	if (game_init(game) == false)
		return (false);
	return (load_all_textures(game));
}
