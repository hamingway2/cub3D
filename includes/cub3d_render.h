/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_render.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 19:59:08 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/27 19:59:10 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_RENDER_H
# define CUB3D_RENDER_H

# include "cub3d_structs.h"

int		draw_loop(t_game *game);
void	put_pixel(int x, int y, int colour, t_game *game);
void	draw_square(t_game *game, t_square square);
void	draw_minimap(t_game *game);
void	draw_minimap_player(t_game *game, int cell_size);
void	draw_player_rays(t_game *game, int cell_size);
void	clear_image(t_game *game);
void	draw_background(t_game *game);
void	draw_raycasting(t_game *game);
void	draw_textured_column(t_game *game, t_ray *ray, int screen_x);
void	init_ray(t_ray *ray, t_game *game, double ray_angle);

#endif
