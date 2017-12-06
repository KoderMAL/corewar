/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfile.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 16:36:08 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/05 18:17:01 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENFILE_H
# define OPENFILE_H

# define BUFF_SIZE 1024

typedef struct		s_openfile
{
	int				fd;
	char			buffer[BUFF_SIZE];
	int				pos;
	int				buff_size;
}					t_openfile;

void				openfile_init(t_openfile *of, int fd);
int					openfile_read_char(t_openfile *of, char *c);
void				openfile_write_char(t_openfile *of, char c);
void				openfile_flush(t_openfile *of);
void				openfile_write_str(t_openfile *fd, char *str, int end);
void				openfile_write_nbr(t_openfile *fd, int *nbr, int end);

#endif
