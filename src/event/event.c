/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 15:17:48 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/29 18:07:10 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_release(int key, t_game *game)
{
	if (key == W)
		game->player.key_up = false;
	if (key == S)
		game->player.key_down = false;
	if (key == D)
		game->player.key_right = false;
	if (key == A)
		game->player.key_left = false;
	if (key == KEY_LEFT)
		game->player.key_turn_left = false;
	if (key == KEY_RIGHT)
		game->player.key_turn_right = false;
	return (0);
}

// TODO: Could be renamed to key_press instead of event
int	key_press(int key, t_game *game)
{
	if (key == KEY_ESC)
		game_close(game);
	if (key == W)
		game->player.key_up = true;
	if (key == S)
		game->player.key_down = true;
	if (key == D)
		game->player.key_right = true;
	if (key == A)
		game->player.key_left = true;
	if (key == KEY_LEFT)
		game->player.key_turn_left = true;
	if (key == KEY_RIGHT)
		game->player.key_turn_right = true;
	return (0);
}

int	game_close(t_game *game)
{
	mlx_loop_end(game->mlx);
	return (0);
}

void	game_loop(t_game *game)
{
	mlx_hook(game->window, 2, 1L << 0, key_press, game);
	mlx_hook(game->window, 3, 1L << 1, key_release, game);
	mlx_hook(game->window, 17, 0, game_close, game);
	mlx_loop_hook(game->mlx, draw_loop, game);
	mlx_loop(game->mlx);
}
