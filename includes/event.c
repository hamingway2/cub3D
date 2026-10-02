#include "cub3d.h"

int	key_event(int key, t_game *game)
{
	if (key == KEY_ESC)
		game_close(game);
	return (0);
}

int game_close(t_game *game)
{
	game_destroy_event(game, EXIT_SUCCESS);
	return (0);
}