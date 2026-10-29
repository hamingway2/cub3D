/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 15:11:16 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/12 16:23:22 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_texture(t_game *game)
{
	printf("\n--- Textures ---\n");
	printf("North:   %s\n", game->north.path);
	printf("South:   %s\n", game->south.path);
	printf("West:    %s\n", game->west.path);
	printf("East:    %s\n", game->east.path);
}

static void	print_color(t_game *game)
{
	printf("\n--- Colors ---\n");
	printf("Floor:   %X\n", game->floor_color);
	printf("Ceiling: %X\n", game->ceiling_color);
}

static void	print_map(t_game *game)
{
	int	i;

	printf("\n--- Map ---\n");
	printf("Width:  %d\n", game->map.width);
	printf("Height: %d\n", game->map.height);
	if (game->map.grid)
	{
		i = 0;
		while (i < game->map.height)
		{
			printf("%3d: [%s]\n", i, game->map.grid[i]);
			i++;
		}
	}
}

static void	print_player(t_game *game)
{
	printf("\n--- Player ---\n");
	printf("X:         %.2f\n", game->player.x);
	printf("Y:         %.2f\n", game->player.y);
	printf("Direction: %.2f degrees\n", game->player.direction);
	printf("Plane X:   %.2f\n", game->player.plane_x);
	printf("Plane Y:   %.2f\n", game->player.plane_y);
}

void	print_game(t_game *game)
{
	printf("========== GAME ==========\n");
	print_texture(game);
	print_color(game);
	print_map(game);
	print_player(game);
	printf("\n==========================\n");
}
