#include "cub3d.h"

int	error_msg(char *msg)
{
	ft_putstr_fd(ERROR, 2);
	ft_putstr_fd(msg, 2);
	return (FALSE);
}

void	free_map(t_map *map)
{
	int	i;

	if (map->grid)
	{
		i = 0;
		while (map->grid[i])
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
		map->grid = NULL;
	}
}

void	mlx_cleanup(t_game *game)
{
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
}

void	game_cleanup(t_game *game)
{
	free(game->texture_north);
	free(game->texture_south);
	free(game->texture_west);
	free(game->texture_east);
	free(game->floor_color);
	free(game->ceiling_color);
	free_map(&game->map);
	mlx_cleanup(game);
}

void	game_destroy(t_game *game, int exit_status)
{
	game_cleanup(game);
	exit(exit_status);
}
