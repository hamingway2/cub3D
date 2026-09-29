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

int	main(int argc, char **argv)
{
	(void)argv;

	//check arguments
	if (argc != 2)
	{
		ft_putstr(ERROR, 2);
		ft_putstr(USAGE_INFO, 2);
		return (1);
	}
	if (ft_strcmp(argv[1], HELP_FLAG))
	{
		ft_putstr(USAGE_INFO, 1);
		return (1);
	}
	ft_putstr("cub3d started!\n", 1);
	return (0);
}
