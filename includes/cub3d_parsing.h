#ifndef CUB3D_PARSING_H
# define CUB3D_PARSING_H

# include "cub3d_structs.h"

int		parse_file(t_game *game, char *filename);
int		validate_map(t_game *game);
int		normalize_map(t_map *map);
int		parse_config(t_game *game, char *line);
int		is_empty_line(char *line);
int		is_config_line(char *line);
int		is_map_line(char *line);
int		is_texture_line(char *line);
int		is_color_line(char *line);
int		is_player_char(char c);
int		get_line_length(char *line);
char	*get_next_line(int fd);

#endif
