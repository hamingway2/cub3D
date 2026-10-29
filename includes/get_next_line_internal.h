/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_internal.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 22:49:29 by gkhavari          #+#    #+#             */
/*   Updated: 2026/10/29 20:20:05 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_INTERNAL_H
# define GET_NEXT_LINE_INTERNAL_H

char	*gnl_read_line(int fd, char *left_over_chars, int *read_error);
void	gnl_setup_line(char *line_buffer, char **left_over_chars);

#endif
