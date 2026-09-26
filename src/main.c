/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 17:17:30 by azielnic          #+#    #+#             */
/*   Updated: 2026/09/26 21:03:13 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	exit_free(t_game *game, int status)
{
	// mlx_destroy_image(game->mlx, game->image);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(status);
}

int	key_handler(int keycode, void *in)
{
	t_game	*game;

	game = (t_game *)in;
	if (keycode == XK_Escape)
		exit_free(game, EXIT_SUCCESS);
	return (0);
}

int	click_handler(void *in)
{
	t_game	*game;

	game = (t_game *)in;
	exit_free(game, EXIT_SUCCESS);
	return (0);
}

void game_init(t_game *game)
{
	ft_bzero(game, sizeof(*game));
	game->mlx = mlx_init();
	if (!game->mlx)
		exit(EXIT_FAILURE);
	game->window = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (!game->window)
		exit_free(game, EXIT_FAILURE);
	
	mlx_hook(game->window, 2, KeyPressMask, &key_handler, game);
	mlx_hook(game->window, 17, StructureNotifyMask, &click_handler, game);
	
	mlx_loop(game->mlx);
	
}

int	main(int argc, char **argv)
{
	t_game	game;
	(void)argv;

	if (argc != 2)
	{
		printf("Usage: ./cub3d maps/<map.cub>\n");
		return (1);
	}
	printf("cub3d started!\n");
	game_init(&game);
	return (0);
}
