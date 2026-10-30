/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 20:17:53 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/29 20:56:21 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * Initializes MiniLibX, records the display dimensions, and creates a
 * screen-sized window and render image. Returns true on success, or reports
 * an error and returns false if initialization fails.
 */

int	game_init(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (error_msg("MiniLibX initialization failed\n"));
	mlx_get_screen_size(game->mlx, &game->display_width,
		&game->display_height);
	if (game->display_width < 2 || game->display_height < 1)
		return (error_msg("Could not determine screen dimensions\n"));
	game->screen_width = game->display_width;
	game->screen_height = game->display_height;
	game->window = mlx_new_window(game->mlx, game->display_width,
			game->display_height, "cub3d");
	if (!game->window)
		return (error_msg("Could not create MiniLibX window\n"));
	game->img.img = mlx_new_image(game->mlx, game->screen_width,
			game->screen_height);
	if (!game->img.img)
		return (error_msg("Could not create MiniLibX image\n"));
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	if (!game->img.addr)
		return (error_msg("Could not access MiniLibX image data\n"));
	return (true);
}

/*
 * Chooses dimensions for the next window, toggling between display size and
 * a window at three-quarters of the display dimensions.
 */
static void	get_window_dimensions(t_game *game, int *width, int *height)
{
	*width = game->display_width;
	*height = game->display_height;
	if (!game->windowed)
	{
		*width = game->display_width * 3 / 4;
		*height = game->display_height * 3 / 4;
		if (*width < 1)
			*width = 1;
		if (*height < 1)
			*height = 1;
	}
}

/* Creates a render image of the requested dimensions and retrieves its data. */
static int	init_resized_image(t_game *game, int width, int height,
		t_img *image)
{
	image->img = mlx_new_image(game->mlx, width, height);
	if (!image->img)
		return (error_msg("Could not resize game image\n"));
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
			&image->line_length, &image->endian);
	if (!image->addr)
	{
		mlx_destroy_image(game->mlx, image->img);
		image->img = NULL;
		return (error_msg("Could not access resized game image data\n"));
	}
	return (true);
}

/* Toggles the window size and recreates its image and event hooks. */
int	resize_game_window(t_game *game)
{
	void	*new_window;
	int		new_width;
	int		new_height;
	t_img	new_img;

	get_window_dimensions(game, &new_width, &new_height);
	new_window = mlx_new_window(game->mlx, new_width, new_height, "cub3d");
	if (!new_window)
		return (error_msg("Could not resize game window\n"));
	if (!init_resized_image(game, new_width, new_height, &new_img))
	{
		mlx_destroy_window(game->mlx, new_window);
		return (false);
	}
	mlx_destroy_image(game->mlx, game->img.img);
	mlx_destroy_window(game->mlx, game->window);
	game->window = new_window;
	game->img = new_img;
	game->screen_width = new_width;
	game->screen_height = new_height;
	game->windowed = !game->windowed;
	register_window_hooks(game->window, game);
	return (true);
}

int	game_setup(t_game *game, char *file)
{
	ft_bzero(game, sizeof(*game));
	if (parse_file(game, file) == false)
		return (false);
	if (player_init(game) == false)
		return (false);
	if (game_init(game) == false)
		return (false);
	return (load_all_textures(game));
}
