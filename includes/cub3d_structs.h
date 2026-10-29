/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 19:59:17 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/27 19:59:19 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCTS_H
# define CUB3D_STRUCTS_H

# include <stdbool.h>

typedef struct s_parse
{
	int	map_started;
	int	map_height;
	int	capacity;
}	t_parse;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_texture
{
	t_img	img;
	char	*path;
	int		width;
	int		height;
}	t_texture;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	double	perp_dist;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
}	t_ray;

typedef struct s_wall
{
	t_texture	*texture;
	double		tex_step;
	double		tex_pos;
	int			tex_x;
	int			height;
	int			start_y;
	int			end_y;
}	t_wall;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	direction;
	double	plane_x;
	double	plane_y;
	bool	key_up;
	bool	key_down;
	bool	key_right;
	bool	key_left;
	bool	key_turn_left;
	bool	key_turn_right;
}	t_player;

typedef struct s_square
{
	int	x;
	int	y;
	int	size;
	int	colour;
}	t_square;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	int			screen_width;
	int			screen_height;
	t_texture	north;
	t_texture	south;
	t_texture	west;
	t_texture	east;
	int			floor_color;
	int			ceiling_color;
	bool		floor_color_set;
	bool		ceiling_color_set;
	t_map		map;
	t_player	player;
	t_img		img;
}	t_game;

#endif
