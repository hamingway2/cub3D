/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 20:17:53 by gkhavari          #+#    #+#             */
/*   Updated: 2026/09/29 20:17:55 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
//TODO: maybe add error message for mlx function failure
void	game_init(t_game *game)
{
	int	width;
	int	height;

	ft_bzero(game, sizeof(*game));
	game->mlx = mlx_init();
	if (!game->mlx)
		game_destroy(game, EXIT_FAILURE);
	mlx_get_screen_size(game->mlx, &width, &height);
	game->window = mlx_new_window(game->mlx, width, height, "cub3d");
	if (!game->window)
		game_destroy(game, EXIT_FAILURE);
	game->img.img = mlx_new_image(game->mlx, width, height);
	if (!game->img.img)
		game_destroy(game, EXIT_FAILURE);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	if (!game->img.addr)
		game_destroy(game, EXIT_FAILURE);
}

//Later
// int	window_init(t_game *game);
// int	image_init(t_game *game);
