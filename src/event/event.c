/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 15:17:48 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/08 15:17:49 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_event(int key, t_game *game)
{
	if (key == KEY_ESC)
		game_close(game);
	return (0);
}

int	game_close(t_game *game)
{
	game_destroy(game, EXIT_SUCCESS);
	return (0);
}
