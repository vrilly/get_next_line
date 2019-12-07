/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <tjans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/07 19:23:31 by tjans         #+#    #+#                 */
/*   Updated: 2019/12/07 19:24:34 by tjans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
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
typedef struct	s_blist
{
	t_buffer		*buffer;
	int				fd;
	struct s_blist	*next;
}				t_blist;
int				get_next_line(int fd, char **line);
t_buffer		*util_initbuffer(t_blist **blist, int fd);
void			util_rmbuffer(t_blist **blist, t_buffer *buff);
#endif
