/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 15:11:45 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/29 18:11:25 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Checks whether a path ends with the supplied extension. */
int	has_extension(char *filename, char *extension)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < ft_strlen(extension)
		|| ft_strncmp(filename + len - ft_strlen(extension),
			extension, ft_strlen(extension) + 1) != 0)
		return (false);
	return (true);
}

/* Checks that the basename contains a name before the supplied extension. */
int	has_filename_before_extension(char *filename, char *extension)
{
	char	*basename;

	basename = ft_strrchr(filename, '/');
	if (basename)
		basename++;
	else
		basename = filename;
	return (ft_strlen(basename) > ft_strlen(extension));
}

/* Validates the argument count and map filename, reporting any errors. */
int	check_arguments(int ac, char **av)
{
	if (ac != 2)
		return (error_msg(USAGE_INFO));
	if (has_extension(av[1], EXTENSION) == false)
		return (error_msg(WRONG_EXT));
	if (has_filename_before_extension(av[1], EXTENSION) == false)
		return (error_msg(INVALID_FILE_NAME));
	return (true);
}
