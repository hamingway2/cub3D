/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 20:17:53 by gkhavari          #+#    #+#             */
/*   Updated: 2026/09/29 20:17:55 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
//TODO: maybe add error message for mlx function failure
void	game_init(t_game *game)
{
	int	width;
	int	height;

	ft_bzero(game, sizeof(*game));
	game->mlx = mlx_init();
	if (!game->mlx)
		destroy_event(game, EXIT_FAILURE);
	mlx_get_screen_size(game->mlx, &width, &height);
	game->window = mlx_new_window(game->mlx, width, height, "cub3d");
	if (!game->window)
		destroy_event(game, EXIT_FAILURE);
	game->img.img = mlx_new_image(game->mlx, width, height);
	if (!game->img.img)
		destroy_event(game, EXIT_FAILURE);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	if (!game->img.addr)
		destroy_event(game, EXIT_FAILURE);
}

int	parse_file(t_game *game, char *filename)
{
	int		fd;
	char	*line;

	//load map from file
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error_msg(OPEN_ERROR));
	line = get_next_line(fd);
	while (line)
	{
		if (is_empty_line(line))
			;
		else if (is_config_line(line))
			parse_config(game, line);
		else
		{
			load_map(game, fd, line);
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (TRUE);
}
