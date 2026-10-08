/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 17:17:30 by azielnic          #+#    #+#             */
/*   Updated: 2026/10/08 17:56:48 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <sys/time.h>

int	draw_loop(t_game *game)
{
	t_player				*player;
	static struct timeval	last_frame_time;
	struct timeval			current_time;
	double					frame_delta;

	gettimeofday(&current_time, NULL);
	frame_delta = (double)current_time.tv_sec
		+ (double)current_time.tv_usec / 1000000.0;
	if (last_frame_time.tv_sec != 0 || last_frame_time.tv_usec != 0)
		frame_delta -= (double)last_frame_time.tv_sec
			+ (double)last_frame_time.tv_usec / 1000000.0;
	else
		frame_delta = 0.0;
	last_frame_time = current_time;
	player = &game->player;
	clear_image(game);
	rotate_player(player, frame_delta);
	move_player(player, game, frame_delta);
	draw_minimap(game);
	// draw_map(game);
	mlx_put_image_to_window(game->mlx, game->window, game->img.img, 0, 0);
	return (0);
}

//////////////////////////////// Gitis part

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc == 2 && ft_strncmp(argv[1], HELP_FLAG,
			ft_strlen(HELP_FLAG) + 1) == 0)
		return (ft_putstr_fd(USAGE_INFO, 1), EXIT_SUCCESS);
	if (check_arguments(argc, argv) == FALSE)
		return (EXIT_FAILURE);
	if (game_setup(&game, argv[1]) == FALSE)
		return (EXIT_FAILURE);
	print_game(&game); // Print the game state for debugging purposes
	game_loop(&game);
	game_destroy(&game, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
