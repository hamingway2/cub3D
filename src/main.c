/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 17:17:30 by azielnic          #+#    #+#             */
/*   Updated: 2026/10/07 22:22:42 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	collision_minimap(double px, double py, t_game *game)
{
	int	x;
	int	y;

	x = (int)floor(px);
	y = (int)floor(py);
	if (x < 0 || x >= game->map.width || y < 0 || y >= game->map.height)
		return (true);
	return (game->map.grid[y][x] == WALL);
}

void	move_player(t_player *player)
{
	double	speed;
	double	angle;
	double	move_x;
	double	move_y;

	speed = 0.05;
	angle = player->direction * PI / 180.0;
	move_x = 0.0;
	move_y = 0.0;
	if (player->key_up)
	{
		move_x += sin(angle) * speed;
		move_y -= cos(angle) * speed;
	}
	if (player->key_down)
	{
		move_x -= sin(angle) * speed;
		move_y += cos(angle) * speed;
	}
	if (player->key_left)
	{
		move_x -= cos(angle) * speed;
		move_y -= sin(angle) * speed;
	}
	if (player->key_right)
	{
		move_x += cos(angle) * speed;
		move_y += sin(angle) * speed;
	}
	player->x += move_x;
	player->y += move_y;
}

void	clear_image(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0x000000, game);
			x++;
		}
		y++;
	}
}

int	game_loop(t_game *game)
{
	t_player	*player;
	// TODO: angle can be avoided if direction directly stores radians instead of degrees
	double		angle; 
	double		ray_x;
	double		ray_y;
	double		step_x;
	double		step_y;
	
	player = &game->player;
	clear_image(game);
	move_player(player);
	draw_minimap(game);
	// draw_map(game);

	ray_x = player->x;
	ray_y = player->y;
	angle = player->direction * PI / 180.0;
	step_x = +sin(angle);
	step_y = -cos(angle);
	
	while (!collision_minimap(ray_x, ray_y, game))
	{
		put_pixel(ray_x, ray_y, 0xFF0000, game);
		ray_x += step_x;
		ray_y += step_y;
	}
	
	mlx_put_image_to_window(game->mlx, game->window, game->img.img, 0, 0);
	return (0);
}

//////////////////////////////// Gitis part

int	error_msg(char *msg)
{
	ft_putstr_fd(ERROR, 2);
	ft_putstr_fd(msg, 2);
	return (FALSE);
}

int	has_cub_extension(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (FALSE);
	return (ft_strncmp(filename + len - ft_strlen(EXTENSION),
			EXTENSION, ft_strlen(EXTENSION) + 1) == 0);
}

int	check_arguments(int ac, char **av)
{
	if (ac != 2)
		return (error_msg(USAGE_INFO));
	if (has_cub_extension(av[1]) == FALSE)
		return (error_msg(WRONG_EXTENSION));
	return (TRUE);
}

void	print_map(char **grid, int height, int width)
{
	int	i;
	int	j;

	ft_putstr_fd("Printing a map of height ", 1);
	ft_putnbr_fd(height, 1);
	ft_putstr_fd(" and width ", 1);
	ft_putnbr_fd(width, 1);
	ft_putstr_fd(".\n\n", 1);
	i = 0;
	while (grid[i] != NULL)
	{
		j = 0;
		while (grid[i][j] != '\0')
		{
			ft_putchar_fd(grid[i][j], 1);
			j++;
		}
		i++;
	}
	ft_putchar_fd('\n', 1);
}

//this will be used to get the real height of the map, as get_map_height() is not working properly yet (to be deleted later)
int	get_real_map_height(t_map *map)
{
	int	i;

	i = 0;
	while (map->grid[i] != NULL)
		i++;
	map->height = i;
	return (i);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc == 2 && ft_strncmp(argv[1], HELP_FLAG,
			ft_strlen(HELP_FLAG) + 1) == 0)
	{
		ft_putstr_fd(USAGE_INFO, 1);
		return (0);
	}
	if (check_arguments(argc, argv) == FALSE)
		return (1);
	game_init(&game);
	if (parse_file(&game, argv[1]) == FALSE)
		return (1);
	//hardcoding real map height for now, as get_map_height() is not working properly yet
	game.map.height = get_real_map_height(&game.map);
	//testing map output
	// print_map(game.map.grid, game.map.height, game.map.width); // Testfunktion
	if (player_init(&game) == FALSE)
		return (1);
	mlx_hook(game.window, 2, 1L << 0, key_event, &game);
	mlx_hook(game.window, 3, 1L << 1, key_release, &game);
	//mlx_mouse_hook(game.window, mouse_event, &state);
	mlx_hook(game.window, 17, 0, game_close, &game);

	mlx_loop_hook(game.mlx, game_loop, &game);

	mlx_loop(game.mlx);
	game_destroy(&game, EXIT_SUCCESS);
	return (0);
}
