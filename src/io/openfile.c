/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 13:44:43 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/05 14:32:13 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "openfile.h"

void		openfile_init(t_openfile *of, int fd)
{
	of->fd = fd;
	of->pos = 0;
	of->buff_size = 0;
}

int			openfile_read_char(t_openfile *of, char *c)
{
	if (of->pos == of->buff_size)
	{

		of->buff_size = read(of->fd, of->buffer, BUFF_SIZE);
		of->pos = 0;
		if (of->buff_size == 0)
			return (0);
	}
	*c = of->buffer[of->pos];
	of->pos++;
	return (1);
}

void		openfile_write_char(t_openfile *of, char c)
{
	of->buffer[of->pos] = c;
	of->pos++;
	if (of->pos == BUFF_SIZE)
	{
		write(of->fd, of->buffer, BUFF_SIZE);
		of->pos = 0;
	}
}

void		openfile_flush(t_openfile *of)
{
	write(of->fd, of->buffer, of->pos);
	of->pos = 0;
}
