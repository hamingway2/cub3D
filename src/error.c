/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 20:14:47 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/27 20:14:49 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	error_msg(char *msg)
{
	ft_putstr_fd(ERROR, 2);
	ft_putstr_fd(msg, 2);
	return (FALSE);
}

int	error_line(char *msg, char *line)
{
	error_msg(msg);
	ft_putchar_fd('"', 2);
	while (*line && *line != '\n')
		ft_putchar_fd(*line++, 2);
	ft_putstr_fd("\"\n", 2);
	return (FALSE);
}
