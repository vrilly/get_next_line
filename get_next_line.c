/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <tjans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/11 22:05:23 by tjans         #+#    #+#                 */
/*   Updated: 2019/11/21 17:34:35 by tjans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_buffer(int fd, t_buffer *buff)
{
	if (buff->b_pos < buff->b_read && buff->b_read != 0)
		return (1);
	buff->b_read = read(fd, buff->buff, BUFFER_SIZE);
	if (buff->b_read > 0)
		buff->b_pos = 0;
	return (buff->b_read > 0);
}

static int	extend_lb(char **line, size_t *lb_size)
{
	char	*newbuf;
	size_t	i;

	newbuf = malloc(*lb_size + BUFFER_SIZE);
	if (!newbuf)
		return (0);
	i = 0;
	while (i < *lb_size)
	{
		newbuf[i] = (*line)[i];
		i++;
	}
	free(*line);
	*line = newbuf;
	*lb_size += BUFFER_SIZE;
	return (1);
}

static int	find_line(int fd, t_buffer *buff, char **line)
{
	size_t	lb_size;
	size_t	i;

	lb_size = BUFFER_SIZE;
	i = 0;
	if (buff->b_pos >= buff->b_read && buff->b_read > 0)
		read_buffer(fd, buff);
	while (buff->b_pos < buff->b_read)
	{
		if (buff->buff[buff->b_pos] == '\n')
		{
			(*line)[i] = '\0';
			buff->b_pos++;
			return (read_buffer(fd, buff));
		}
		(*line)[i] = buff->buff[buff->b_pos];
		i++;
		buff->b_pos++;
		if (i >= lb_size && !extend_lb(line, &lb_size))
			return (-1);
		if (buff->b_read != 0 && buff->b_pos == buff->b_read)
			read_buffer(fd, buff);
	}
	(*line)[i] = '\0';
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static t_buffer	*buff;
	int				ret;

	ret = 0;
	if (!line || fd < 0)
		return (-1);
	*line = malloc(BUFFER_SIZE);
	if (!*line)
		return (-1);
	buff = util_initbuffer(fd, buff);
	ret = find_line(fd, buff, line);
	if (ret <= 0 || buff->b_read < 0)
	{
		if (buff->b_read < 0)
			ret = -1;
		free(buff);
		buff = NULL;
	}
	if (ret == -1)
		*line = NULL;
	return (ret);
}
