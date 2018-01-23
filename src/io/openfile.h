/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfile.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 16:36:08 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/23 16:24:54 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENFILE_H
# define OPENFILE_H

# include <stdlib.h>

# define BUFF_SIZE 1024

typedef struct		s_openfile
{
	int				fd;
	char			buffer[BUFF_SIZE];
	int				pos;
	int				buff_size;
}					t_openfile;

/*
** openfile.c
*/

void				openfile_init(t_openfile *of, int fd);
int					openfile_read_char(t_openfile *of, char *c);
void				openfile_write_char(t_openfile *of, char c);
void				openfile_flush(t_openfile *of);

/*
** openfile_write.c
*/

void				openfile_write_buf(t_openfile *of, char *buf, size_t len);
void				openfile_write_str(t_openfile *fd, char *str, int endl);
void				openfile_write_nbr(t_openfile *fd, int nbr, int endl);

#endif
