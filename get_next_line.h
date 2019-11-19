/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <tjans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/11 22:05:31 by tjans         #+#    #+#                 */
/*   Updated: 2019/11/14 15:17:48 by tjans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_buffer
{
	char	buff[BUFFER_SIZE];
	ssize_t	b_read;
	ssize_t	b_pos;
	int		fd;
}				t_buffer;
int				get_next_line(int fd, char **line);
t_buffer		*util_initbuffer(int fd, t_buffer *old_buff);
#endif
