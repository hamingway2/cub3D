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

/* Checks whether the path ends with the required .cub extension. */
int	has_cub_extension(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < ft_strlen(EXTENSION)
		|| ft_strncmp(filename + len - ft_strlen(EXTENSION),
			EXTENSION, ft_strlen(EXTENSION) + 1) != 0)
		return (false);
	return (true);
}

/* Validates the argument count and map filename, reporting any errors. */
int	check_arguments(int ac, char **av)
{
	char	*basename;

	if (ac != 2)
		return (error_msg(USAGE_INFO));
	if (has_cub_extension(av[1]) == false)
		return (error_msg(WRONG_EXTENSION));
	basename = ft_strrchr(av[1], '/');
	if (basename)
		basename++;
	else
		basename = av[1];
	if (ft_strlen(basename) == ft_strlen(EXTENSION))
		return (error_msg(INVALID_FILE_NAME));
	return (true);
}
