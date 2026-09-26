#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <mlx.h>
# include <X11/keysym.h>	// used for keys
# include <X11/X.h>			// used for mouse and key hooks

# ifndef WIDTH
#  define WIDTH 800
# endif

# ifndef HEIGHT
#  define HEIGHT 800
# endif


typedef	struct s_game
{
	void		*mlx;
	void		*window;
	// void		*image;

	// t_player	player;
}	t_game;

int	main(int argc, char **argv);

#endif