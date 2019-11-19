/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <tjans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/11 22:05:23 by tjans         #+#    #+#                 */
/*   Updated: 2019/11/19 22:26:57 by tjans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static t_blist	*list;
	t_buffer		*buff;
	ssize_t			i;
	int				ret;

	if (!line || fd < 0)
		return (-1);
	*line = malloc(BUFFER_SIZE);
	i = 0;
	ret = 0;
	buff = util_initbuffer(&list, fd);
	if (!*line || !buff)
		return (-1);
	ret = find_line(fd, buff, line);
	if (!ret)
		util_rmbuffer(&list, buff);
	return (ret);
}
