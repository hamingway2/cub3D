#include "cub3d.h"

int	key_release(int key, t_game *game)
{
	if (key == W)
		game->player.key_up = false;
	if (key == S)
		game->player.key_down = false;
	if (key == D)
		game->player.key_right = false;
	if (key == A)
		game->player.key_left = false;
	return (0);
}

// TODO: Could be renamed to key_press instead of event
int	key_event(int key, t_game *game)
{
	if (key == KEY_ESC)
		game_close(game);
	if (key == W)
		game->player.key_up = true;
	if (key == S)
		game->player.key_down = true;
	if (key == D)
		game->player.key_right = true;
	if (key == A)
		game->player.key_left = true;
	return (0);
}

int game_close(t_game *game)
{
	game_destroy(game, EXIT_SUCCESS);
	return (0);
}
