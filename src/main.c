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
	ft_putstr(ERROR, 2);
	ft_putstr(msg, 2);
	return (1);
}

int	main(int argc, char **argv)
{
	(void)argv;

	if (ft_strcmp(argv[1], HELP_FLAG))
	{
		ft_putstr(USAGE_INFO, 1);
		return (0);
	}

	//check arguments
	if (argc != 2)
		return (error_msg(USAGE_INFO));

	ft_putstr("cub3d started!\n", 1);
	return (0);
}
