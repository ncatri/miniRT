/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 12:55:32 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/22 11:26:55 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

# define FDS_LIM	256
# define BUF_LINE_LIM	1

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_file
{
	int		fd;
	char	buffer[BUFFER_SIZE];
	size_t	position;
	size_t	size;
	int		eof;
	int		bad;
}				t_file;

typedef struct s_buf
{
	char	*tmp;
	size_t	pos;
	size_t	size;
}				t_buf;

int		get_next_line(int fd, char **line);
int		initialize_buf_c(t_buf *b, char *c);
void	check_tfile(t_file **f, int fd);
int		free_and_zero(t_file **f);

#endif
