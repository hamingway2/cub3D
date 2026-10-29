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

// Could think about setting variables to NULL after freeing or destroying

int	error_msg(char *msg)
{
	ft_putstr_fd(ERROR, 2);
	ft_putstr_fd(msg, 2);
	return (FALSE);
}

static void	free_texture(t_game *game, t_texture *texture)
{
	if (game->mlx && texture->img.img)
		mlx_destroy_image(game->mlx, texture->img.img);
	texture->img.img = NULL;
	texture->img.addr = NULL;
	free(texture->path);
	texture->path = NULL;
}

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
	if (!game)
		return ;
	get_next_line(-1); //cleanup gnl buffer in case of failure
	free_texture(game, &game->north);
	free_texture(game, &game->south);
	free_texture(game, &game->west);
	free_texture(game, &game->east);
	free_map(&game->map);
	mlx_cleanup(game);
}

void	game_destroy(t_game *game, int exit_status)
{
	game_cleanup(game);
	exit(exit_status);
}
