/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 22:40:00 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/29 18:10:48 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/get_next_line_internal.h"

static char	*append_buffer(char *line, char *buffer, int bytes_read)
{
	char	*joined_line;

	buffer[bytes_read] = '\0';
	if (!line)
		return (ft_strjoin("", buffer));
	joined_line = ft_strjoin(line, buffer);
	free(line);
	return (joined_line);
}

static char	*read_error_line(char *line, int *read_error)
{
	if (read_error)
		*read_error = true;
	free(line);
	return (NULL);
}

static char	*fill_line(int fd, char *line, char *buffer, int *read_error)
{
	int	bytes_read;

	while (!line || !ft_strchr(line, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			return (line);
		if (bytes_read < 0)
			return (read_error_line(line, read_error));
		line = append_buffer(line, buffer, bytes_read);
		if (!line)
			return (NULL);
	}
	return (line);
}

char	*gnl_read_line(int fd, char *left_over_chars, int *read_error)
{
	char	*buffer;
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(left_over_chars);
		return (NULL);
	}
	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
	{
		free(left_over_chars);
		return (NULL);
	}
	line = fill_line(fd, left_over_chars, buffer, read_error);
	free(buffer);
	return (line);
}

void	gnl_setup_line(char *line_buffer, char **left_over_chars)
{
	size_t	i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == '\n')
	{
		*left_over_chars = ft_substr(line_buffer, i + 1,
				ft_strlen(line_buffer) - i);
		line_buffer[i + 1] = '\0';
	}
}
