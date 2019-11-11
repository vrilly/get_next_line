/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <tjans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/11 22:05:23 by tjans         #+#    #+#                 */
/*   Updated: 2019/11/11 22:55:28 by tjans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	read_buffer(t_buffer *buff)
{
}

int get_next_line(int fd, char **line)
{
	static t_buffer	*buff;
	ssize_t			line_size;

	if (!buff)
		buff = util_initbuffer(fd);
	while (buff->bytes_read > 0)
	{
		line_size = util_getnlpos(buff);
		if (line_size == buff->bytes_read)
			read_buffer(buff);
	}
}
