/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 14:13:38 by ncatrien          #+#    #+#             */
/*   Updated: 2021/02/26 11:36:58 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	free_ret(void *ptr, int value)
{
	free(ptr);
	return (value);
}

static t_file	*open_f(int fd)
{
	t_file	*fpt;

	fpt = malloc(1 * sizeof(t_file));
	if (fpt)
	{
		fpt->fd = fd;
		fpt->position = 0;
		fpt->size = 0;
		fpt->eof = 0;
		fpt->bad = 0;
	}
	return (fpt);
}

static int	get_char(t_file *f)
{
	char	c;
	ssize_t	read_ret;

	if (!f)
		return (-1);
	if (f->position >= f->size)
	{
		read_ret = read(f->fd, f->buffer, BUFFER_SIZE);
		if (read_ret > 0)
		{
			f->position = 0;
			f->size = read_ret;
		}
		else if (read_ret == 0)
		{
			f->eof = 1;
			return (0);
		}
		else
			f->bad = 1;
	}
	c = f->buffer[f->position];
	f->position++;
	return (c);
}

static int	append(char **buf, size_t *pos_ptr, size_t *size_ptr, char c)
{
	char	*tmp;

	if (*pos_ptr >= *size_ptr)
	{
		tmp = malloc(sizeof(char) * (*size_ptr + BUF_LINE_LIM));
		if (!tmp)
			return (free_ret(*buf, 0));
		else
		{
			ft_memcpy(tmp, *buf, *size_ptr);
			*size_ptr = *size_ptr + BUF_LINE_LIM;
			free(*buf);
			*buf = tmp;
		}
	}
	(*buf)[*pos_ptr] = c;
	(*pos_ptr)++;
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static	t_file	*f;
	char			c;
	t_buf			b;

	if (fd < 0 || fd >= FDS_LIM || !line || BUFFER_SIZE == 0)
		return (-1);
	if ((b.tmp = malloc(BUF_LINE_LIM * sizeof(char))) == 0)
		return (-1);
	b.pos = 0;
	b.size = BUF_LINE_LIM;
	if (f == 0)
		f = open_f(fd);
	while ((c = get_char(f)) != '\n' && f->eof == 0)
		if ((f->bad && free_ret(f, 1)) || !append(&b.tmp, &b.pos, &b.size, c))
			return (free_ret(b.tmp, -1));
	if (!append(&b.tmp, &b.pos, &b.size, '\0'))
		return (free_ret(b.tmp, -1));
	*line = b.tmp;
	if (f->eof)
	{
		free(f);
		f = 0;
		return (0);
	}
	return (1);
}
