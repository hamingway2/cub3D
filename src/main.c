/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 17:17:30 by azielnic          #+#    #+#             */
/*   Updated: 2026/09/26 17:20:31 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	game_loop(&game);
	game_destroy(&game, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
