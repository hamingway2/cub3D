/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 20:10:34 by gkhavari          #+#    #+#             */
/*   Updated: 2026/09/29 20:10:57 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <mlx.h>

// Macro Definition
# define TRUE 1
# define FALSE 0
# define USAGE_INFO "Usage: ./cub3d maps/<map.cub>\n"
# define HELP_FLAG "--help"
# define EXTENSION ".cub"

//Error msg
# define ERROR "Error\n"
# define INVALID_FILENAME "Invalid file name\n"
# define WRONG_EXTENSION "Invalid file extension\n"

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

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
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	t_map		map;
	t_player	player;
	t_img		img;
}	t_game;

int	main(int argc, char **argv);

#endif
