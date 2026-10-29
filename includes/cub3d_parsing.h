/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parsing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 19:59:01 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/27 19:59:03 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_PARSING_H
# define CUB3D_PARSING_H

# include "cub3d_structs.h"

int		parse_file(t_game *game, char *filename);
int		read_map_file(t_game *game, int fd, t_parse *parse);
int		validate_config(t_game *game);
int		validate_map(t_game *game);
int		validate_map_walls(t_game *game);
int		normalize_map(t_map *map);
int		parse_config(t_game *game, char *line);
int		parse_color(t_game *game, char *line);
int		duplicate_config(char *identifier);
int		is_empty_line(char *line);
int		is_config_line(char *line);
int		is_map_line(char *line);
int		is_texture_line(char *line);
int		is_color_line(char *line);
int		is_player_char(char c);
int		get_line_length(char *line);
char	*get_next_line(int fd, int *read_error);

#endif
