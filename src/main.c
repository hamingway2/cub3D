/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 17:17:30 by azielnic          #+#    #+#             */
/*   Updated: 2026/09/26 17:20:31 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int error_msg(char *msg)
{
	ft_putstr_fd(ERROR, 2);
	ft_putstr_fd(msg, 2);
	return (FALSE);
}

int	has_cub_extension(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (FALSE);
	return (ft_strncmp(filename + len - ft_strlen(EXTENSION), EXTENSION, ft_strlen(EXTENSION) + 1) == 0);
}

int	check_arguments(int ac, char **av)
{
	if (ac != 2)
		return (error_msg(USAGE_INFO));
	if (has_cub_extension(av[1]) == FALSE)
		return (error_msg(WRONG_EXTENSION));
	if (ft_strlen(av[1]) < 5)
		return (error_msg(INVALID_FILENAME));
	return (TRUE);
}

int	main(int argc, char **argv)
{
	if (argc == 2 && ft_strncmp(argv[1], HELP_FLAG, ft_strlen(HELP_FLAG) + 1) == 0)
	{
		ft_putstr_fd(USAGE_INFO, 1);
		return (0);
	}
	if (check_arguments(argc, argv) == FALSE)
		return (1);

	ft_putstr_fd("cub3d started!\n", 1);
	return (0);
}
