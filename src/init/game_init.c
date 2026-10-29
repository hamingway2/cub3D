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

void	init_player_plane(t_player *player)
{
	double	angle;
	double	plane_length;

	angle = player->direction * PI / 180;
	plane_length = tan((FOV / 2.0) * PI / 180.0);
	player->plane_x = cos(angle) * plane_length;
	player->plane_y = -sin(angle) * plane_length;
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
				init_player_plane(&game->player);
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
	ft_bzero(game, sizeof(*game));
	if (parse_file(game, file) == FALSE)
		return (FALSE);
	if (player_init(game) == FALSE)
		return (FALSE);
	return (game_init(game));
}

int	game_init(t_game *game)
{
	int	width;
	int	height;

	game->mlx = mlx_init();
	if (!game->mlx)
		return (error_msg("MiniLibX initialization failed\n"));
	mlx_get_screen_size(game->mlx, &width, &height);
	game->window = mlx_new_window(game->mlx, width, height, "cub3d");
	if (!game->window)
		return (error_msg("Could not create MiniLibX window\n"));
	game->img.img = mlx_new_image(game->mlx, width, height);
	if (!game->img.img)
		return (error_msg("Could not create MiniLibX image\n"));
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	if (!game->img.addr)
		return (error_msg("Could not access MiniLibX image data\n"));
	return (TRUE);
}
