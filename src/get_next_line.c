/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:54:10 by gkhavari          #+#    #+#             */
/*   Updated: 2025/06/10 11:58:40 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/get_next_line_internal.h"

char	*get_next_line(int fd, int *read_error)
{
	char		*next_line;
	static char	*left_over_chars = NULL;

	if (read_error)
		*read_error = FALSE;
	next_line = gnl_read_line(fd, left_over_chars, read_error);
	left_over_chars = NULL;
	if (!next_line)
		return (NULL);
	gnl_setup_line(next_line, &left_over_chars);
	if (!next_line[0])
	{
		free(next_line);
		return (NULL);
	}
	return (next_line);
}
