/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <tjans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/11 22:05:39 by tjans         #+#    #+#                 */
/*   Updated: 2019/11/14 15:19:16 by tjans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

t_buffer	*util_initbuffer(int fd, t_buffer *old_buff)
{
	t_buffer	*buff;

	if (old_buff && old_buff->fd == fd)
		return (old_buff);
	if (old_buff)
		free(old_buff);
	buff = malloc(sizeof(t_buffer));
	buff->b_pos = 0;
	buff->b_read = read(fd, buff->buff, BUFFER_SIZE);
	buff->fd = fd;
	return (buff);
}
