/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 16:36:08 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/05 13:48:49 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# define BUFF_SIZE 1


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


/* Library functions */
size_t				ft_strlen(const char *s);
#endif
