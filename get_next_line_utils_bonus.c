/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <tjans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/11 22:05:39 by tjans         #+#    #+#                 */
/*   Updated: 2019/11/14 17:18:54 by tjans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static t_buffer	*create_buffer(int fd)
{
	t_buffer	*buff;

	buff = malloc(sizeof(t_buffer));
	if (!buff)
		return (NULL);
	buff->b_pos = 0;
	buff->b_read = read(fd, buff->buff, BUFFER_SIZE);
	buff->fd = fd;
	return (buff);
}

static int		blist_append(t_blist **blist, t_buffer *buff)
{
	t_blist *i;

	if (!*blist)
	{
		*blist = malloc(sizeof(t_blist));
		if (!*blist)
			return (0);
		(*blist)->buffer = buff;
		(*blist)->fd = buff->fd;
		(*blist)->next = NULL;
		return (1);
	}
	i = *blist;
	while (i->next)
		i = i->next;
	i->next = malloc(sizeof(t_blist));
	i = i->next;
	if (!i)
		return (0);
	i->buffer = buff;
	i->fd = buff->fd;
	i->next = NULL;
	return (1);
}

static t_buffer	*blist_findbuffer(t_blist **blist, int fd)
{
	t_buffer	*buff;
	t_blist		*i;

	if (!*blist)
	{
		buff = create_buffer(fd);
		if (!buff || !blist_append(blist, buff))
			return (NULL);
		return (buff);
	}
	i = *blist;
	while (i)
	{
		if (i->fd == fd)
			return (i->buffer);
		i = i->next;
	}
	buff = create_buffer(fd);
	if (!buff || !blist_append(blist, buff))
		return (NULL);
	return (buff);
}

t_buffer		*util_initbuffer(t_blist **blist, int fd)
{
	t_buffer	*buff;

	buff = blist_findbuffer(blist, fd);
	return (buff);
}

void			util_rmbuffer(t_blist **blist, t_buffer *buff)
{
	t_blist	*i;
	t_blist *prev;

	i = *blist;
	prev = NULL;
	if (!i)
		return ;
	while (i)
	{
		if (i->fd == buff->fd)
		{
			if (prev)
				prev->next = i->next;
			else if (!i->next)
				*blist = NULL;
			free(buff);
			free(i);
			return ;
		}
		prev = i;
		i = i->next;
	}
}
