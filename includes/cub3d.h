#ifndef CUB3D_H
# define CUB3D_H

// # include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

typedef	struct s_game
{
	void	*mlx;
	void	*window;
}	t_game;

int	main(int argc, char **argv);

#endif