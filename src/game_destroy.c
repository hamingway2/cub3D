/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 15:13:15 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/12 16:36:38 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_map *map)
{
	int	i;

	if (map->grid)
	{
		i = 0;
		while (map->grid[i])
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
		map->grid = NULL;
	}
}

void	mlx_cleanup(t_game *game)
{
	if (!game)
		return ;
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
}

void	game_cleanup(t_game *game)
{
	get_next_line(-1, NULL); //cleanup gnl buffer in case of failure
	free(game->texture_north);
	free(game->texture_south);
	free(game->texture_west);
	free(game->texture_east);
	free_map(&game->map);
	mlx_cleanup(game);
}
