/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 17:17:30 by azielnic          #+#    #+#             */
/*   Updated: 2026/10/08 17:46:35 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <sys/time.h>

static bool	is_wall_cell(t_game *game, int map_x, int map_y)
{
	if (map_x < 0 || map_y < 0 || map_x >= game->map.width
		|| map_y >= game->map.height)
		return (true);
	return (game->map.grid[map_y][map_x] == WALL);
}

bool	collision_minimap(double x, double y, t_game *game)
{
	int	map_x;
	int	map_y;

	map_x = (int)floor(x - PLAYER_RADIUS);
	map_y = (int)floor(y - PLAYER_RADIUS);
	if (is_wall_cell(game, map_x, map_y))
		return (true);
	map_x = (int)floor(x + PLAYER_RADIUS);
	if (is_wall_cell(game, map_x, map_y))
		return (true);
	map_y = (int)floor(y + PLAYER_RADIUS);
	if (is_wall_cell(game, map_x, map_y))
		return (true);
	map_x = (int)floor(x - PLAYER_RADIUS);
	if (is_wall_cell(game, map_x, map_y))
		return (true);
	return (false);
}

static void	get_movement_vector(t_player *player, double delta_time,
		double *move_x, double *move_y)
{
	double	angle;
	double	forward_x;
	double	forward_y;
	double	strafe_x;
	double	strafe_y;
	int		move_count;

	angle = player->direction * PI / 180.0;
	forward_x = sin(angle);
	forward_y = -cos(angle);
	strafe_x = cos(angle);
	strafe_y = sin(angle);
	*move_x = 0.0;
	*move_y = 0.0;
	move_count = 0;
	if (player->key_up)
		move_count++;
	if (player->key_down)
		move_count++;
	if (player->key_left)
		move_count++;
	if (player->key_right)
		move_count++;
	if (move_count == 0)
		return ;
	if (player->key_up)
	{
		*move_x += forward_x;
		*move_y += forward_y;
	}
	if (player->key_down)
	{
		*move_x -= forward_x;
		*move_y -= forward_y;
	}
	if (player->key_left)
	{
		*move_x -= strafe_x;
		*move_y -= strafe_y;
	}
	if (player->key_right)
	{
		*move_x += strafe_x;
		*move_y += strafe_y;
	}
	if (move_count > 1)
	{
		*move_x /= sqrt(2.0);
		*move_y /= sqrt(2.0);
	}
	*move_x *= PLAYER_SPEED * delta_time;
	*move_y *= PLAYER_SPEED * delta_time;
}

void	rotate_player(t_player *player, double delta_time)
{
	double	rotation;

	if (player->key_turn_left == player->key_turn_right)
		return ;
	rotation = TURN_SPEED * delta_time;
	if (player->key_turn_left)
		rotation = -rotation;
	player->direction += rotation;
	while (player->direction < 0.0)
		player->direction += 360.0;
	while (player->direction >= 360.0)
		player->direction -= 360.0;
}

void	move_player(t_player *player, t_game *game, double delta_time)
{
	double	move_x;
	double	move_y;

	if (delta_time < 0.0)
		delta_time = 0.0;
	if (delta_time > 0.1)
		delta_time = 0.1;
	get_movement_vector(player, delta_time, &move_x, &move_y);
	if (!collision_minimap(player->x + move_x, player->y, game))
		player->x += move_x;
	if (!collision_minimap(player->x, player->y + move_y, game))
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
