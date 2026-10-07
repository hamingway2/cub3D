# include  "cub3d.h"

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
		ft_putchar_fd('\n', 1);
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
