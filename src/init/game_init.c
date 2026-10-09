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

#include "cub3d.h"
//TODO: maybe add error message for mlx function failure

static void	init_keys(t_player *player)
{
	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;
	player->key_turn_left = false;
	player->key_turn_right = false;
}

static double	get_player_direction(char player_start)
{
	if (player_start == PLAYER_NORTH)
		return (0.0);
	else if (player_start == PLAYER_EAST)
		return (90.0);
	else if (player_start == PLAYER_SOUTH)
		return (180.0);
	else if (player_start == PLAYER_WEST)
		return (270.0);
	else
		return (-1.0); // Invalid player start character
}

int	player_init(t_game *game)
{
	int	i;
	int	j;

	init_keys(&game->player);
	i = 0;
	while (game->map.grid[i] != NULL)
	{
		j = 0;
		while (game->map.grid[i][j] != '\0')
		{
			if (is_player_char(game->map.grid[i][j]))
			{
				game->player.x = j + 0.5; // Center of the cell
				game->player.y = i + 0.5; // Center of the cell
				game->player.direction
					= get_player_direction(game->map.grid[i][j]);
				return (TRUE);
			}
			j++;
		}
		i++;
	}
	return (error_msg(NO_PLAYER_START));
}

int	game_setup(t_game *game, char *file)
{
	game_init(game);
	if (parse_file(game, file) == FALSE)
		return (FALSE);
	if (player_init(game) == FALSE)
		return (FALSE);
	return (TRUE);
}

void	game_loop(t_game *game)
{
	mlx_hook(game->window, 2, 1L << 0, key_event, game);
	mlx_hook(game->window, 3, 1L << 1, key_release, game);
	mlx_key_hook(game->window, key_event, game);
	//mlx_mouse_hook(game.window, mouse_event, &state);
	mlx_hook(game->window, 17, 0, game_close, game);
	mlx_loop_hook(game->mlx, draw_loop, game);
	mlx_loop(game->mlx);
}

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
