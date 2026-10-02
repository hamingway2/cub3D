/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 17:17:30 by azielnic          #+#    #+#             */
/*   Updated: 2026/10/02 23:57:23 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixel(int x, int y, int colour, t_game *game)
{
	int	index;
		
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->img.line_length + x * game->img.bits_per_pixel / 8;
	game->img.addr[index] = colour & 0xFF;
	game->img.addr[index + 1] = (colour >> 8) & 0xFF;
	game->img.addr[index + 2] = (colour >> 16)& 0xFF;
}

void	draw_player(int x, int y, int size, int colour, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(x + i, y + j, colour, game);
			j++;
		}
		i++;
	}
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

	draw_player(WIDTH / 2, HEIGHT / 2, 10, 0x00FF00, &game);
	mlx_put_image_to_window(game.mlx, game.window, game.img.img, 0, 0);
		
	mlx_key_hook(game.window, key_event, &game);
	//mlx_mouse_hook(game.window, mouse_event, &state);
	mlx_hook(game.window, 17, 0, game_close, &game);
	mlx_loop(game.mlx);
	ft_putstr_fd("cub3d started!\n", 1);
	game_destroy(&game, EXIT_SUCCESS);
	return (0);
}
