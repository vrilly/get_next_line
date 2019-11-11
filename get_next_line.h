/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <tjans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/11 22:05:31 by tjans         #+#    #+#                 */
/*   Updated: 2019/11/11 22:53:44 by tjans         ########   odam.nl         */
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
	ssize_t	bytes_read;
}				t_buffer;
int				get_next_line(int fd, char **line);
ssize_t			util_getnlpos(t_buffer *buff);
t_buffer		*util_initbuffer(int fd);
#endif
