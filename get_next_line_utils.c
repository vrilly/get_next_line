/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <tjans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/11 22:05:39 by tjans         #+#    #+#                 */
/*   Updated: 2019/11/11 22:53:39 by tjans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_buffer	*util_initbuffer(int fd)
{
	t_buffer	*buff;

	buff = malloc(sizeof(t_buffer));
	buff->bytes_read = read(fd, buff, BUFFER_SIZE);
	return (buff);
}

ssize_t		util_getnlpos(t_buffer *buff)
{
	ssize_t	i;

	i = 0;
	while (buff->buff[i] && i < buff->bytes_read)
		i++;
	return (i);
}
