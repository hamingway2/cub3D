/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 15:11:16 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/08 15:11:18 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_texture(t_game *game)
{
	printf("\n--- Textures ---\n");
	printf("North:   %s\n", game->texture_north);
	printf("South:   %s\n", game->texture_south);
	printf("West:    %s\n", game->texture_west);
	printf("East:    %s\n", game->texture_east);
}

static void	print_color(t_game *game)
{
	printf("\n--- Colors ---\n");
	printf("Floor:   %s\n", game->floor_color);
	printf("Ceiling: %s\n", game->ceiling_color);
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
