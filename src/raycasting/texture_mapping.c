/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 17:00:00 by azielnic          #+#    #+#             */
/*   Updated: 2026/10/30 18:33:44 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * Selects the appropriate wall texture based on the side of the wall hit by 
 * the ray and its direction of travel, returning the texture corresponding 
 * to the north, south, east or west wall.
 */

static t_texture	*wall_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0 && ray->dir_x > 0.0)
		return (&game->east);
	if (ray->side == 0)
		return (&game->west);
	if (ray->dir_y > 0.0)
		return (&game->south);
	return (&game->north);
}

/*
 * Calculates the horizontal texture coordinate by finding the exact point 
 * where the ray hits the wall and mapping it to the texture's width. 
 * Adjusts the coordinate based on the wall's orientation to ensure the 
 * texture is displayed in the correct direction.
 */

static int	wall_texture_x(t_game *game, t_ray *ray, t_texture *texture)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = game->player.y + ray->perp_dist * ray->dir_y;
	else
		wall_x = game->player.x + ray->perp_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * texture->width);
	if ((ray->side == 0 && ray->dir_x < 0.0)
		|| (ray->side == 1 && ray->dir_y > 0.0))
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

/*
 * Retrieves the colour of a specific pixel from a texture by calculating
 * its memory address using the pixel coordinates, line length and bits
 * per pixel, then returns the pixel's colour value.
 */

static unsigned int	texture_pixel(t_texture *texture, int x, int y)
{
	int	index;

	index = y * texture->img.line_length
		+ x * (texture->img.bits_per_pixel / 8);
	return (*(unsigned int *)(texture->img.addr + index));
}

/*
 * Prepares the wall for rendering by selecting the correct texture, 
 * calculating the texture's horizontal coordinate, and determining the 
 * wall's height and vertical position based on its distance from the 
 * player. Calculates the texture sampling step and starting position, 
 * then clips the wall to fit within the screen boundaries.
 */

static void	prepare_wall(t_game *game, t_ray *ray, t_wall *wall)
{
	wall->texture = wall_texture(game, ray);
	wall->tex_x = wall_texture_x(game, ray, wall->texture);
	wall->height = (int)((game->screen_width
				/ (2.0 * tan(FOV * PI / 360.0)))
			/ ray->perp_dist);
	if (wall->height < 1)
		wall->height = 1;
	wall->start_y = (game->screen_height - wall->height) / 2;
	wall->end_y = wall->start_y + wall->height;
	wall->tex_step = (double)wall->texture->height / wall->height;
	wall->tex_pos = 0.0;
	if (wall->start_y < 0)
		wall->tex_pos = -wall->start_y * wall->tex_step;
	if (wall->start_y < 0)
		wall->start_y = 0;
	if (wall->end_y >= game->screen_height)
		wall->end_y = game->screen_height - 1;
}

void	draw_textured_column(t_game *game, t_ray *ray, int screen_x)
{
	t_wall	wall;
	int		y;
	int		tex_y;

	prepare_wall(game, ray, &wall);
	y = wall.start_y;
	while (y <= wall.end_y)
	{
		tex_y = (int)wall.tex_pos;
		if (tex_y >= wall.texture->height)
			tex_y = wall.texture->height - 1;
		put_pixel(screen_x, y, texture_pixel(wall.texture, wall.tex_x,
				tex_y), game);
		wall.tex_pos += wall.tex_step;
		y++;
	}
}
