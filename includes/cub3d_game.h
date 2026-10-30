/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_game.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 19:58:54 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/29 20:57:11 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_GAME_H
# define CUB3D_GAME_H

# include "cub3d_structs.h"

int		game_init(t_game *game);
int		player_init(t_game *game);
int		game_setup(t_game *game, char *file);
int		load_all_textures(t_game *game);
void	game_loop(t_game *game);
void	game_cleanup(t_game *game);
void	free_map(t_map *map);
int		error_msg(char *msg);
int		error_line(char *msg, char *line);
int		check_arguments(int ac, char **av);
int		has_extension(char *filename, char *extension);
int		has_filename_before_extension(char *filename, char *extension);
void	print_game(t_game *game);
int		key_press(int key, t_game *game);
int		key_release(int key, t_game *game);
int		game_close(t_game *game);
void	rotate_player(t_player *player, double delta_time);
void	move_player(t_player *player, t_game *game, double delta_time);
bool	collision(double x, double y, t_game *game);
void	get_movement_vector(t_player *player, double delta_time,
			double *move_x, double *move_y);

#endif
