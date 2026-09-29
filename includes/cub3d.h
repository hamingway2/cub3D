#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

// Macro Definition
#define USAGE_INFO "Usage: ./cub3d maps/<map.cub>\n"
#define ERRPR "Error\n"
#define HELP_FLAG "--help"

typedef	struct s_game
{
	void	*mlx;
	void	*window;
}	t_game;

int	main(int argc, char **argv);

#endif